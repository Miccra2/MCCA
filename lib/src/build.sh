LIBDIR=/mnt/d/projects/mcca/lib
BINDIR=$LIBDIR/bin
SRCDIR=$LIBDIR/src

gcc -c -g $SRCDIR/list.c -o $BINDIR/list.o
gcc -c -g $SRCDIR/reader.c -o $BINDIR/reader.o

ar rcs $BINDIR/liblist.a $BINDIR/list.o
ar rcs $BINDIR/libreader.a $BINDIR/reader.o

rm -rf $BINDIR/*.o
