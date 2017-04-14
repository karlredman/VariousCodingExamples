CC = g++
INCLUDES = -I../../../3rdparty/v3p/include -I../../../3rdparty/GNU/include
LIBDIRS = -L/opt/v3p/lib -L/opt/sfw/lib

all: proj3

proj3:
	$(CC) $@.cc -o ../bin/$@ $(INCLUDES) $(LIBDIRS) -lGNUruntime -lV3Pruntime 

clean:
	rm -f ../bin/*
	rm -f ./*.o
	rm -f ./*~
