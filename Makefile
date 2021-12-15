CC = gcc
AR = ar
OBJECTS_MAIN = main.o
OBJECTS_HEADER = Ex3.h
FLAGS = -Wall -g

all: strings

strings: $(OBJECTS_MAIN) Ex3.a
	$(CC) $(FLAGS) -o strings $(OBJECTS_MAIN) Ex3.a

Ex3.a: $(OBJECTS_MAIN)
	$(AR) -rcs Ex3.a # $(OBJECTS) # create static library

main.o: main.c $(OBJECTS_HEADER)
	$(CC) $(FLAGS) -c main.c

clean:
	rm -f *.o *.a strings