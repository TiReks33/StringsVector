default: strings_vector_x86.lib

strings_vector_x86.lib: strings_vector_private.c strings_vector_private.h strings_vector.h
	i686-w64-mingw32-gcc -D_WIN32_WINNT=0x0502 -c strings_vector_private.c -o strings_vector_x86.lib
	
clean:
	-@rm -f strings_vector_x86.lib 2>/dev/null 



