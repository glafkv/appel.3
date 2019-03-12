CC	= gcc
CFLAGS	= -g

all: main worker

main:	main.c
	$(CC) -o main main.c

worker:	worker.c
	$(CC) -o worker worker.c

.PHONY: clean
clean:
	/bin/rm -f *.o *~ main
	/bin/rm -f *.o *~ worker
