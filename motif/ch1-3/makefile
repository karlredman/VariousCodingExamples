CC=gcc
LIBS= -lXm -lXt -lX11
DIRS= -L/usr/X11/lib -I/usr/X11/include

TARGET = label scale text size1 size2 font anomaly

all: $(TARGET)

$(TARGET):
	$(CC) $@.c -o $@ $(DIRS) $(LIBS) -g

new:
	$(MAKE) clean
	$(MAKE) all

clean:
	rm -f $(TARGET) *~
