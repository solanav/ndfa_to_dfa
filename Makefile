# NAMES
EXEC_NAME=mach

# FOLDERS
INCLUDE=include/
SRC=src/
BIN=bin/

# COMPILER
CC=gcc
CFLAGS=-g -Wall $(LIBS)
LIBS=-lm

all: mk $(EXEC_NAME) rm

# CREATE AND REMOVE BIN
mk:
	mkdir -p $(BIN)

rm:
	rm -rf $(BIN)

# MAIN EXECUTABLE
$(EXEC_NAME): main.o transforma.o afnd.o afnd_plus.o lambda_parser.o
	$(CC) -o $@ $(BIN)main.o $(BIN)transforma.o $(BIN)afnd.o $(BIN)afnd_plus.o $(BIN)lambda_parser.o $(CFLAGS)

# OBJECTS
main.o: $(SRC)main.c
	$(CC) -c -o $(BIN)$@ $< $(CFLAGS)

afnd.o: $(SRC)afnd.c
	$(CC) -c -o $(BIN)$@ $<

afnd_plus.o: $(SRC)afnd_plus.c
	$(CC) -c -o $(BIN)$@ $< $(CFLAGS)

transforma.o: $(SRC)transforma.c
	$(CC) -c -o $(BIN)$@ $< $(CFLAGS)

lambda_parser.o: $(SRC)lambda_parser.c
	$(CC) -c -o $(BIN)$@ $< $(CFLAGS)

# UTILS
valgrind:
	valgrind --leak-check=full ./$(EXEC_NAME)

dot:
	for f in *.dot; do dot -Tpng $f > $f.png; done

clean:
	rm -f *.dot *.png $(EXEC_NAME)