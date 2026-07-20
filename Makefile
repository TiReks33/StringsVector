default: strings_vector_lib.o

strings_vector_lib.o: strings_vector_private.c strings_vector_private.h strings_vector.h
	gcc -c strings_vector_private.c -o strings_vector_lib.o

clean:
	-@rm -f strings_vector*.o 2>/dev/null 



