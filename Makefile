main: main.o person.o elevator.o
	gcc -o main main.o person.o elevator.o -lncurses

person.o: person.c person.h
	gcc -c person.c

main.o: person.c person.h elevator.c elevator.h main.c
	gcc -c main.c person.c elevator.c 

elevator.o: elevator.c elevator.h person.c person.h
	gcc -c elevator.c person.c
clean :
	rm -f main *.o


