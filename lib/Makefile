AR = ar
ARFLAGS = -rcs ${LIBRARY} ${OBJFILE}

CC = cc
CFLAGS = -g -c ${FILE} -o ${OBJFILE}

FILE = list.c
OBJFILE = bin/list.o
LIBRARY = liblist.a

list.a:
	${CC} ${CFLAGS}
	${AR} ${ARFLAGS}
