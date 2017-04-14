CC = g++
INCLUDES = -I../include
CFLAGS = $(INCLUDES)

INSTDIR = /opt/verascape

TARGET = libVstatic.a libVruntime.so 

.cc.o:
	$(CC) -c $(CFLAGS) $<

all: $(TARGET) move

libVstatic.a: static.o
	$(AR) rv $@ static.o

libVruntime.so: runtime.o
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
