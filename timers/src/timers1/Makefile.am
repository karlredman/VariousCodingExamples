include_HEADERS = \
	mThread.h \
	Timer.h
INCLUDES = -I$(top_srcdir)/include -I. 
CPPFLAGS = -g -Wall
LDFLAGS = -lpthread 
LIBS = /usr/lib/libposixtime.a
#
bin_PROGRAMS = timertest1
timertest1_SOURCES = \
	timertest.cc \
	mThread.cc \
	Timer.cc
