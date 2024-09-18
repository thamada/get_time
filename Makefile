#Time-stamp: <2024-09-18 14:09:25 hamada>
CC=gcc
CFLAGS=-Wall -std=gnu99

all: run.x
	./run.x

run.x: get_time.o main.o
	${CC} ${CFLAGS} $^ -o $@

c: clean

clean:
	rm -rf *~ .*~
	rm -f run.x
	rm -f *.o


