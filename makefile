CC=g++
CFLAGS=-pthread -Wall -lrt 

all: main.out

main.out: main.cpp
	$(CC) $(CFLAGS) main.cpp -o proc.out

clean:
	rm -f proc.out
