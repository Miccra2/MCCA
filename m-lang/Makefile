CC=cc
AR=ar
RM=rm

all: main clean

main:
	$(CC) -g -c list.c -o list.o
	$(AR) rcs liblist.a list.o
	$(CC) -g main.c -o main -I. -L. -l:liblist.a

clean:
	$(RM) *.o
