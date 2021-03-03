OBJS := main.o filelist.o process.o

CFLAGS := -O2 -W -Wall

.PHONY: all, clean

all: lsofp

lsofp: $(OBJS)
	cc -o lsofp $(OBJS)

main.o: process.h filelist.h
process.o: process.h filelist.h
filelist.o: filelist.h

clean:
	rm $(OBJS)
