#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "strings_vector.h"
#include "count_time.h"


// leaks!! need to 'free'
char * get_random_string(size_t lim_siz, char ** outp) {

    srand((unsigned int)(get_cur_time().tv_nsec));

    char charset[] = "0123456789"
                     "abcdefghijklmnopqrstuvwxyz"
                     "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    size_t length = 1 + rand() % (lim_siz);

    char * dest = (char*) malloc(sizeof(char) * length + 1);

    for(size_t i = 0; i != length; ++i) {
        size_t char_index = (double) rand() / RAND_MAX * (sizeof charset - 1);
        dest[i] = charset[char_index];
    }
    dest[length] = '\0';

    if(outp)
        *outp = dest;

    return dest;
}


int main(int argc, char * argv[])
{
    size_t iter = 1000000;

    strings_vector * sv = sv_init(&sv);

    strings_vector * sv2 = sv_init(&sv2);


    char * cstr = NULL;//get_random_cstr(1000, &cstr);

    timespec push_time = get_cur_time();

    for(size_t i =0; i != iter; ++i)
    {
        sv_push_back(sv, get_random_string(1000, &cstr));
        //printf("capacity: %d;\n", sv_capacity(sv));
        free(cstr);
    }

    printf("time expired(push):%f\n", time_passed(push_time));

    sv_shrink_to_fit(sv);

    printf("capacity: %d;\n", sv_capacity(sv));

    timespec copy_time = get_cur_time();

    sv_copy(sv2,sv);

    printf("time expired(copy):%f\n", time_passed(copy_time));

    timespec move_time = get_cur_time();

    sv_move(sv,sv2);

    printf("time expired(move):%f\n", time_passed(move_time));

    //printf("%s\n", Bool2S(True));

strings_vector * vect = sv_init(NULL); // 1st method of obj init -- via return

strings_vector * vect2 = NULL;

sv_init(&vect2); // 2nd method of obj init -- init via obj address arg

sv_push_back(vect, "Test string"); // add element to 'vect'

sv_push_back(vect2, "Abc Def Ghi"); // add element to 'vect2'

sv_push_back(vect2, "Тестовая строка"); // add element to 'vect2'

char const * last_str = sv_get(vect2, sv_size(vect2) - 1); // get last element of 'vect2'

sv_copy(vect2, vect); // copy content of 'vect' and add to back of 'vect2'

sv_print_nl(vect2); // 'sugar' print of content in 'vect2' :)

strings_vector * vect3;

sv_init(&vect3);

sv_push_back(vect3, "Cool str");

sv_move(vect3, vect2); // move all content from 'vect2' to 'vect3'

sv_print_nl(vect2); // now 'vect2' is empty!

printf("size of vect2: %d;\n", sv_size(vect2));

sv_print_nl(vect3); // 'vect3' now have "Cool str" string + all content of 'vect2' 

printf("size of vect3: %d;\n", sv_size(vect3));

sv_replace_string(vect3, 1, "Абв Где Жзи"); // replace 2nd C-string inside 'vect3' with "Абв Где Жзи"

char ** array_of_strings = (char**) sv_data(vect3); // get underlying array of C-strings inside 'vect3',
						    // and cast it to non-const pointer for able to 
						    // modify strings literals (allowed, because 
						    // dynamically allocated C-strings used inside!)

array_of_strings[0][3] = 'L'; // change 4th literal of 1st string in 'vect3' ('Cool str' -> 'CooL str')

printf("'vect3' after some changes:\n");

sv_print_nl(vect3);


sv_free(vect); // freeing memory

sv_free(vect2);

sv_free(vect3);

    sv_free(sv);

    sv_free(sv2);
}



