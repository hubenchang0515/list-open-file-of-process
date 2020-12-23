OBJS := main.o filelist.o process.o

CC := gcc -g

.PONEY: all, clean

all: lsofp

lsofp: $(OBJS)
	gcc -o lsofp $(OBJS)

main.o:process.h
process.o: process.h filelist.h
filelist.o: filelist.h

clean:
	rm $(OBJS)