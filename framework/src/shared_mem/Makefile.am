EXTRA_DIST = class_SHMem.h class_SHMemConsumer.h class_SHMemProducer.h
#
INCLUDES = -I$(top_srcdir)/include
LDFLAGS = -L$(top_srcdir)/lib
CPPFLAGS = -g -Wall
#
bin_PROGRAMS = SHMemProducer
#
SHMemProducer_SOURCES = \
	class_SHMem.C \
	class_SHMemProducer.C \
	producer.C
