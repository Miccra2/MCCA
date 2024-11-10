CC=cc
AR=ar
RM=rm

all: remove com-run
com-run: com run
com: libs main clean

remove:
	$(RM) mcc

libs:
	$(CC) -g -c list.c -o list.o
	$(AR) rcs liblist.a list.o

main:
	$(CC) -g main.c -o mcc -I. -L. -l:liblist.a -Wall -Wextra

clean:
	$(RM) *.o

check:
	$(VALGIRND) -s --leak-check=full ./mcc

run:
	./mcc test0.mcs
