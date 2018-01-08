.PHONY: all clean
all: encrypt decrypt runtest

clean:
	rm -f crypto.o main.o test.o encrypt decrypt runtest

main.o: main.c
	gcc -Wall -c main.c

crypto.o: crypto.c
	gcc -Wall -c crypto.c

encrypt: main.o crypto.o
	gcc -o encrypt main.o crypto.o

decrypt: main.o crypto.o
	gcc -o decrypt main.o crypto.o

test.o: test.c
	gcc -Wall -c test.c

runtest : crypto.o test.o
	gcc -o runtest test.o crypto.o
	./runtest
