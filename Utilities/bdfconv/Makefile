
.PHONY:	all clean


CFLAGS += -g
CFLAGS += -Os

INCLUDEPATHS += -I .

all: bdfconv

bdfconv: bdfconv.o
	$(CC) $(LDFLAGS) bdfconv.o -o bdfconv

bdfconv.o: bdfconv.c
	$(CC) $(CFLAGS) $(INCLUDEPATHS) bdfconv.c -c -o bdfconv.o
	
clean:
	rm bdfconv bdfconv.o
