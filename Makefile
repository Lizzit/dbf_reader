# -*- Makefile -*-

main: main.o
	gcc main.o -o dbfreader

main.o: main.c
	gcc -c main.c

clean:
	rm *.o dbfreader
