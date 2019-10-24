EXEC_NAME=mach

CC=gcc
CFLAGS=-g -Wall
LIBS=-lm

all: $(EXEC_NAME)

$(EXEC_NAME): main.o transforma.o afnd.o
	$(CC) -o $@ $^ $(CFLAGS)

main.o: main.c afnd.h transforma.h
	$(CC) -c -o $@ $< $(CFLAGS)

transforma.o: transforma.c transforma.h
	$(CC) -c -o $@ $< $(CFLAGS)

afnd.o: afnd.c afnd.h
	$(CC) -c -o $@ $<

valgrind:
	valgrind --leak-check=full ./$(EXEC_NAME)

clean:
	rm *.o $(EXEC_NAME)