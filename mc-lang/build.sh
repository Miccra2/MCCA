LIBPATH=/mnt/d/projects/mcca/lib
BINPATH=$LIBPATH/bin
SRCPATH=$LIBPATH/src

cc -g main.c -o mcc -I$SRCPATH -L$BINPATH -llist -lreader
