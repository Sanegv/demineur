run: compile
	./main

compile: main.o demineur.o
	gcc -Wall -o main main.o demineur.o -g

main.o: main.c demineur.o
	gcc -Wall -c main.c demineur.h demineur.c -g

demineur.o: demineur.c demineur.h
	gcc -Wall -c demineur.c demineur.h -g

valgrind: compile
	valgrind ./main

clean:
	rm *.o
	rm *.gch