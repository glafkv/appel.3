CC	= gcc -pthread -lrt
CFLAGS	= -g

all: master palin

master:	master.c
	$(CC) -o master master.c

palin:	palin.c
	$(CC) -o palin palin.c

.PHONY: clean
clean:
	/bin/rm -f *.o *~ master
	/bin/rm -f *.o *~ palin
	/bin/rm -f *.out *~ palin
	/bin/rm -f *.out *~ nopalin
