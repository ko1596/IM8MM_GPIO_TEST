
###export PKG_CONFIG_PATH+=/usr/local/lib/pkgconfig
###export ARCH+=arm64
###export CROSS_COMPILE+=/usr/bin/aarch64-linux-gnu-gcc
###export JSON_C_DIR+=/usr/local/

PWD = $(shell pwd)
##SRC = testjsonc.c

TARGET = spitest

CC=aarch64-linux-gnu-gcc
#CC=gcc

##CFLAGS += $(--cflags json-c)
##LDFLAGS += $(--libs json-c)
#CFLAGS += $(shell pkg-config --cflags json-c)
#LDFLAGS += $(shell pkg-config --libs json-c)
#LDFLAGS += -pthread


OBJS = 	./SPItest.o


all: $(OBJS) $(TARGET)

$(TARGET): 
	$(CC) $(OBJS) -o $@ 

clean:
	rm -f $(TARGET) *.elf *.gdb *.o
	rm -f $(OBJS)
