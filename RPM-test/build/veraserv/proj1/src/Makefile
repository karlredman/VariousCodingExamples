CC = g++
INCLUDES = -I../../proj2/include -I../../../3rdparty/GNU/include
LIBDIRS = -L/opt/sfw/lib -L../../proj2/lib

all: proj1

proj1:
	$(CC) $@.cc -o ../bin/$@ $(INCLUDES) $(LIBDIRS) -lGNUruntime -lVruntime 

clean:
	rm -f ../bin/*
	rm -f ./*.o
	rm -f ./*~
