#sun	CC	= CC
CC	= g++
INC	= 
LIBS	=
CFLAGS	= -g $(INC)

OBJS	= align.o mkalign.o

TARGET  = alignModel

align.o: align.cc mkalign.cc
	$(CC) $(CFLAGS) align.cc mkalign.cc -o $(TARGET)

clean :
	rm -rf core *~
	rm -rf *.o
	rm -f $(TARGET)

new :
	$(MAKE) clean 
	$(MAKE)
