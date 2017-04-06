CFLAGS= -Wall -g
LDFLAGS=
CC= gcc

SRC= t1.c t2.c
OBJS= $(SRC:.c=.o)

all: main

main: main.c $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	@(rm -f *~ *.o)
