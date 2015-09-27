INC_FLAGS = -L./
CFLAGS = -Weverything $(INC_FLAGS)
CC ?= cc

all:
	mkdir -p bin
	$(CC) *.c $(CFLAGS) -O3 -o bin/test

clean:
	rm -rf bin/*

test:
	mkdir -p bin
	$(CC) *.c $(CFLAGS) -O1 -g -o bin/test
