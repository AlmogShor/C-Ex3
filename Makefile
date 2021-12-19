CC = gcc
AR = ar
OBJECTS_MAIN = main.o
OBJECTS_HEADER = string_functions.h
FLAGS = -Wall -g

all: stringProg

stringProg: $(OBJECTS_MAIN) string_functions.a
	$(CC) $(FLAGS) -o stringProg $(OBJECTS_MAIN) string_functions.a

string_functions.a: $(OBJECTS_MAIN)
	$(AR) -rcs string_functions.a # create static library

main.o: main.c $(OBJECTS_HEADER)
	$(CC) $(FLAGS) -c main.c

clean:
	rm -f *.o *.a stringProg