CC = g++
INCLUDES = -I../include
CFLAGS = $(INCLUDES)

INSTDIR = /opt/v3p

TARGET = libV3Pstatic.a libV3Pruntime.so 

.cc.o:
	$(CC) -c $(CFLAGS) $<

all: $(TARGET) move

libV3Pstatic.a: static.o
	$(AR) rv $@ static.o

libV3Pruntime.so: runtime.o
	$(CC) $(DEBUGFLAG) -shared -Wl,-soname,$@ -o $@ $< $(LDFLGS)

move:
	mv *.so ../lib
	mv *.a ../lib

install: all
	cp ../lib/*.so $(INSTDIR)/lib
	cp ../lib/*.a $(INSTDIR)/lib

clean:
	rm -rf *.a *.o *~ *.so
	rm -rf ../lib/*
