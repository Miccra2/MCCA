CC		= cc
CFLAGS	= -I$(LIBPATH) -L$(LIBPATH) -llist
LIBPATH = /home/miccra/projects/mcca/lib

OBJS = list_test.elf l_test.elf
all: $(OBJS)

$(OBJS): %.elf: %.c
	$(CC) -g $< -o $@ $(CFLAGS)
