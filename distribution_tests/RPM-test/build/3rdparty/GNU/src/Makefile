CC = g++
INCLUDES = -I../include
CFLAGS = $(INCLUDES)

INSTDIR = /opt/sfw

TARGET = libGNUstatic.a libGNUruntime.so 

.cc.o:
	$(CC) -c $(CFLAGS) $<

all: $(TARGET) move

libGNUstatic.a: static.o
	$(AR) rv $@ static.o

libGNUruntime.so: runtime.o
	$(CC) $(DEBUGFLAG) -shared -Wl,-soname,$@ -o $@ $< $(LDFLGS)

move:
	mv *.so ../lib
	mv *.a ../lib

install: all
	cp ../lib/*.so $(INSTDIR)/lib
	cp ../lib/*.a $(INSTDIR)/lib
	cp ../include/*.h $(INSTDIR)/include

clean:
	rm -rf *.a *.o *~ *.so
	rm -rf ../lib/*
