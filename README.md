# StringsVector
## Description
C strings container implementation, analog of C++'s std::vector\<std::string\>. It's purpose is more high-level automatation of operations with C-strings without manual memory allocations and other routines. Includes basic functionality API, such as push_back, pop_back, getting size, capacity, copy, move, shrink_to_fit. Supports both pointers to empty C-strings and NULL pointers to C-strings to add.  
**Full user's API with detailed description you can find in public API header file ('strings_vector.h').**
## Comparison between 'StringsVector' and C++ std::vector\<std::string\>:

1000000 (1 million) random strings, 1000 length of each string.

**'std::vector\<std::string\>'**:  
> time expired(push):6.614502  
capacity:1000000  
time expired(copy):0.295728  
time expired(move):0.039745  
  
**'strings_vector'**:  
> time expired(push):6.465033  
capacity: 1000000;  
time expired(copy):0.263102  
time expired(move):0.005524  
  
## Basic usage:

```
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
```

## Additional info

Tested on: Windows XP, Windows 7, Windows 10, Debian 11, Ubuntu 24.04, Fedora 41. 

Checked for memory leaks via 'Valgrind' and 'LeakSanitizer'. 

Necessary non-standard libs and headers for build you can find in mine 'C_stuffs' repo.
