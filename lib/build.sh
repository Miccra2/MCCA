set -xe

CC=gcc
AR=ar
LIBPATH=/mnt/d/projects/mcca/lib

debug() {
    $CC -g -c $LIBPATH/$1.c -o $LIBPATH/$1.o
    $AR rcs $LIBPATH/lib$1.a $LIBPATH/$1.o
}

build() {
    $CC -c $LIBPATH/$1.c -o $LIBPATH/$1.o
    $AR rcs $LIBPATH/lib$1.a $LIBPATH/$1.o
}

clean() {
    rm $LIBPATH/$1.o
}

debug list

clean list
