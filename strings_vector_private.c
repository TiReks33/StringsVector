#include "strings_vector_private.h"
#include "strings_vector.h"


#include <string.h>
#include <stdlib.h>
#include <stdio.h>


// hidden implementation of public's interface


// 1) Object condition WILL BE changed trough execution of this 'methods' :

strings_vector * sv_init(strings_vector ** vect__)
{

    strings_vector * new_vector = (strings_vector *) malloc(sizeof(strings_vector));   
    
    if(!new_vector)
    {
        fprintf(stderr, "'%s' error: 'strings vector' object malloc failed!\n", __func__);
        return NULL; 
    }

    new_vector->arr_ = NULL;
    new_vector->size_ = 0;
    new_vector->alloc_capacity_ = 0;

    if(vect__)
        *vect__ = new_vector;

    return new_vector;

    /*if(!vect__){
        fprintf(stderr, "'%s(..)': expected not null pointer for object in argument.\n", __func__);
       exit(1); 
    }

    *vect__ = (strings_vector *) malloc(sizeof(strings_vector));   

    if(!(*vect__))
    {
        fprintf(stderr, "'%s' error: 'strings vector' object malloc failed!\n", __func__); 
    }
    else
    {
        (*vect__)->arr_ = NULL;
        (*vect__)->size_ = 0;
        (*vect__)->alloc_capacity_ = 0;
    }

    return *vect__;*/
}


void sv_free(strings_vector * vect__)
{
    for(size_t i = 0; i != vect__->size_; ++i)
        free(vect__->arr_[i]);

    free(vect__->arr_);
    
    free(vect__);
}


size_t sv_reserve(strings_vector * v__, size_t n__)
{
    if(n__ > v__->alloc_capacity_) //v__->size_)
    {
        char ** arr_tmp = NULL;
        arr_tmp = (char **) realloc(v__->arr_, sizeof(char *) * n__);

        if(!arr_tmp)
        {
            fprintf(stderr, "'%s' error: realloc for reserving failed!\n", __func__);
        }
        else
        {
            v__->arr_ = arr_tmp;
            v__->alloc_capacity_ = n__;
        }
    }    

    return v__->alloc_capacity_;
}

void sv_shrink_to_fit(strings_vector * v)
{
    if(v->size_ < v->alloc_capacity_)
    {

        if(v->size_)
        {
            char ** arr_tmp = (char **) realloc(v->arr_, sizeof(char *) * v->size_);

            if(!arr_tmp)
            {
                fprintf(stderr, "'%s' error: realloc for reserving failed!\n", __func__);
            }
            else
            {
                v->arr_ = arr_tmp;
                v->alloc_capacity_ = v->size_;
            }
        }
        else
        {
            free(v->arr_);
            v->arr_ = NULL;
            v->alloc_capacity_ = 0;
        }
    }
}

size_t sv_push_back(strings_vector * vect__, char const * new_string__)
{

do{
     // reserve additional slots for future strings if needed
     if(vect__->size_ + 1 > vect__->alloc_capacity_)
     {
         size_t n_siz = (vect__->size_) ? (vect__->size_ * 2) : 1;
         if(sv_reserve(vect__, n_siz) != n_siz)
         {
            fprintf(stderr, "'%s' error: sv_reserve failed!\n", __func__);
            break;
         }       
     }

     // allocate suitable size for new string (to add) inside vector..
     // (checking for null-pointer is carried)
     vect__->arr_[vect__->size_] = NULL;
     if(new_string__)
     {
         vect__->arr_[vect__->size_] = (char*) malloc(strlen(new_string__) + 1);
         if(!vect__->arr_[vect__->size_])
         {
             fprintf(stderr, "'%s' error: malloc for new vector's string failed!\n", __func__);

             break;
         }
        
         strcpy(vect__->arr_[vect__->size_], new_string__);
     
     }

     vect__->size_++;

}while(False);

     return vect__->size_;
}


size_t sv_pop_back(strings_vector * vect__)
{
    if(vect__->size_ > 0){
        free(vect__->arr_[vect__->size_ - 1]);

        //vect__->arr_[vect__->size_ - 1] = NULL; // hmm?..
        
        vect__->size_--;
    }

    return vect__->size_;
}


Bool sv_replace_string(strings_vector * psv__, size_t sv_index_to_replace, char const * new_str__)
{
    if(psv__->size_ < 1 || psv__->size_ <= sv_index_to_replace)
        return False;

    char * tmp_str = NULL;

    if(new_str__)
    {
        tmp_str = (char *) malloc(strlen(new_str__) + 1);
        if(!tmp_str)
        {
            fprintf(stderr, "'%s' error: malloc for new string to replace failed!\n", __func__);
            return False;
        }
        else
        {
            strcpy(tmp_str, new_str__);
        }
    }

    free(psv__->arr_[sv_index_to_replace]);
    
    psv__->arr_[sv_index_to_replace] = tmp_str;

    return True;    
}


void sv_clear(strings_vector * vect__)
{
    for(size_t i =0; i!= vect__->size_; ++i)
    {
        free(vect__->arr_[i]);
    }
    vect__->size_ = 0;
}


strings_vector * sv_copy(strings_vector * recv, strings_vector const * transmit)
{
    do{
    
        /*if(transmit == NULL)
            break;
        */

        for(size_t i = 0; i != sv_size(transmit); ++i)
        {
            sv_push_back(recv, sv_get(transmit, i));
        }
    
    }while(False);
    
    return recv;
}


strings_vector * sv_move(strings_vector * recv, strings_vector * transmit)
{
    do{
        /*
         if(transmit == NULL)
            break;
        */   

        size_t trs = sv_size(transmit);
//            printf("trs:%d;\n", trs);
        size_t rrs = sv_size(recv);
//            printf("rrs:%d;\n", rrs);

        if(sv_capacity(recv) < (trs + rrs))
            sv_reserve(recv, trs + rrs);

        char const ** tmp_v = NULL;
        for(size_t i = 0; i != trs; ++i)
        {
            tmp_v = (char const **) sv_data(recv);
//                printf("tmp_v[rrs + i] before::%s;\n", tmp_v[rrs + i] );
            /*sv_data(recv)*/ tmp_v[rrs + i] = transmit->arr_[i];//sv_get(transmit, i);
//                printf("tmp_v[rrs + i] after::%s;\n", tmp_v[rrs + i] );
            recv->size_++;
            tmp_v = (char const **) sv_data(transmit);
            /*sv_data(transmit)*/ tmp_v[i] = NULL;
            transmit->size_--;
        } 
        
    }while(False);

    return recv;
}


int sv_ascii_order_compar( const void *c_str_p1, const void *c_str_p2)
{
    char const * c_str1 = *((char const * const *) c_str_p1);
    char const * c_str2 = *((char const * const *) c_str_p2);

    if (c_str1 == NULL && c_str2 == NULL)
    {
        return 0;
    }

    if (c_str1 == NULL)
    {
        return 1;
    }

    if (c_str2 == NULL)
    {
        return -1;
    }

    return strcmp(c_str1, c_str2);
}


int sv_ascii_order_compar_desc( const void *c_str_p1, const void *c_str_p2)
{
    char const * c_str1 = *((char const * const *) c_str_p1);
    char const * c_str2 = *((char const * const *) c_str_p2);

    if (c_str1 == NULL && c_str2 == NULL)
    {
        return 0;
    }

    if (c_str1 == NULL)
    {
        return -1;
    }

    if (c_str2 == NULL)
    {
        return 1;
    }

    return strcmp(c_str2, c_str1);
}


void sv_sort(strings_vector * v__, Bool order__)
{
    if(order__)
        qsort(v__->arr_, v__->size_, sizeof(*v__->arr_),sv_ascii_order_compar);
    else
        qsort(v__->arr_, v__->size_, sizeof(*v__->arr_),sv_ascii_order_compar_desc);
}


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


// 2) Object condition will NOT be changed trough execution of this 'methods' :

void sv_print_p(struct strings_vector const * vect__, Bool newline__)
{
    //sv_print(vect__);
    printf("{sv_start}:[");
    for(size_t i = 0; i != vect__->size_; ++i){
        if(newline__)
            printf("\n");
        printf("{%d}:",i);
        printf((vect__->arr_[i])?"\"%s\"":"NULL", vect__->arr_[i]);
        if(i != vect__->size_ - 1)
            printf(";");
        else
            if(newline__)
                printf("\n");
    }
    printf("]:{sv_end}\n");
    fflush(stdout);
}


void sv_print(strings_vector const * vect__)
{
    sv_print_p(vect__, False);
}

void sv_print_nl(strings_vector const * vect__)
{
    sv_print_p(vect__, True);
}

size_t sv_size(strings_vector const * vect__)
{
    return vect__->size_;
}


size_t sv_capacity(strings_vector const * vect__)
{
    return vect__->alloc_capacity_;
}


char const * sv_get(strings_vector const * psv__, size_t index__)
{
    if(psv__->size_ < 1 || index__ >= psv__->size_)
        return NULL;

    return psv__->arr_[index__];
}


char const * sv_get_b(strings_vector const * psv__, size_t index__, Bool * bound)
{
    Bool tb = False;
    char const * tstr = NULL;
    
    do{

        if(!psv__->size_)
        {
            break;
        }

        if(index__ < psv__->size_)
        {
            tb = True;
            tstr = psv__->arr_[index__];
            break;
        }

    }while(False);

    if(bound)
        *bound = tb;

    return tstr;
}


char const * const * sv_data(strings_vector const * vect__)
{
    return (char const * const *) vect__->arr_;
}


Bool sv_empty(strings_vector const * v__)
{
    return (!v__->size_);
}



