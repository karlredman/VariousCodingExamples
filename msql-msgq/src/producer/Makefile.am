INCLUDES = -I$(top_srcdir)/include -I/usr/local/include/mysql
CPPFLAGS = -g -Wall
LDFLAGS = -L/usr/local/lib/mysql -L$(top_srcdir)/lib
LDADD = -lmysqlclient -ldb
#
bin_PROGRAMS = producer
producer_SOURCES = \
        producer.cc 
