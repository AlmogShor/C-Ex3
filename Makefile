CC = gcc
AR = ar
OBJECTS_MAIN = main.o
#OBJECTS = my_mat.o
OBJECTS_HEADER = Ex3.h
FLAGS = -Wall -g

all: connections

connections: $(OBJECTS_MAIN) Ex3.a
	$(CC) $(FLAGS) -o connections $(OBJECTS_MAIN) Ex3.a

Ex3.a: $(OBJECTS_MAIN)
	$(AR) -rcs Ex3.a # $(OBJECTS) # create static library

main.o: main.c $(OBJECTS_HEADER)
	$(CC) $(FLAGS) -c main.c

#my_mat.o: my_mat.c $(OBJECTS_HEADER)
#	$(CC) $(FLAGS) -c my_mat.c

clean:
	rm -f *.o *.a connections