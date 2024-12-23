
CROSS_COMPILE:=/home/G31415/OrangePi4/gcc-aarch64/bin/aarch64-none-linux-gnu-

CC:=$(CROSS_COMPILE)gcc

CFLAGS:=-Wall -O2
LDFLAGS:=-Wall

INCLUDE := -I../common/external/include
LIB := -L../common/external/lib -ljpeg -lfreetype -lpng -lasound -lz -lc -lm

EXESRCS := ../common/graphic.c ../common/touch.c ../common/image.c ../common/task.c $(EXESRCS)

EXEOBJS := $(patsubst %.c, %.o, $(EXESRCS))

$(EXENAME): $(EXEOBJS)
	$(CC) $(LDFLAGS) -o $(EXENAME) $(EXEOBJS) $(LIB)
	cp $(EXENAME) ../out/
	scp -r $(EXENAME) root@192.168.183.168:/root/out/

clean:
	rm -f $(EXENAME) $(EXEOBJS)

%.o: %.c ../common/common.h
	$(CC) $(CFLAGS) $(INCLUDE) -c -o $@ $<

