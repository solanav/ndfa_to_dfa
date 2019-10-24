# NAMES
EXEC_NAME=mach

# FOLDERS
INCLUDE=include/
SRC=src/
BIN=bin/

# COMPILER
CC=gcc
CFLAGS=-g -Wall
LIBS=-lm

all: mk $(EXEC_NAME) rm

# CREATE AND REMOVE BIN
mk:
	mkdir -p $(BIN)

rm:
	rm -rf $(BIN)

# MAIN EXECUTABLE
$(EXEC_NAME): main.o transforma.o afnd.o
	$(CC) -o $@ $(BIN)main.o $(BIN)transforma.o $(BIN)afnd.o $(CFLAGS)

# OBJECTS
main.o: $(SRC)main.c $(INCLUDE)afnd.h $(INCLUDE)transforma.h
	$(CC) -c -o $(BIN)$@ $< $(CFLAGS)

transforma.o: $(SRC)transforma.c $(INCLUDE)transforma.h
	$(CC) -c -o $(BIN)$@ $< $(CFLAGS)

afnd.o: $(SRC)afnd.c $(INCLUDE)afnd.h
	$(CC) -c -o $(BIN)$@ $<

# UTILS
valgrind:
	valgrind --leak-check=full ./$(EXEC_NAME)

dot:
	for f in *.dot; do dot -Tpng $f > $f.png; done

clean:
	rm -f *.dot *.png $(EXEC_NAME)