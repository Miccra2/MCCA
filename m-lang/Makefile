CC=cc
AR=ar
RM=rm

all: list main clean run

list:
	$(CC) -g -c list.c -o list.o
	$(AR) rcs liblist.a list.o

main:
	$(CC) -g main.c -o main -I. -L. -l:liblist.a

clean:
	$(RM) *.o

run:
	./main test.mcs
