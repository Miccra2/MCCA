CC=cc
AR=ar
RM=rm

all: remove com-run
com-run: com run
com: list main clean

remove:
	$(RM) main

list:
	$(CC) -g -c list.c -o list.o
	$(AR) rcs liblist.a list.o

main:
	$(CC) -g main.c -o main -I. -L. -l:liblist.a -Wall -Wextra

clean:
	$(RM) *.o

run:
	./main test0.mcs
