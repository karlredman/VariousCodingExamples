include_HEADERS = \
	hardware_timer.h \
	mytimers.h

INCLUDES = -I$(top_srcdir)/include -I. 
CPPFLAGS = -g -Wall
LDFLAGS = -lpthread 
LIBS = /usr/lib/libposixtime.a
#
bin_PROGRAMS = timertest2
timertest2_SOURCES = \
	hardware_timer.cc \
	mytimers.cc \
	timertest.cc
