INCLUDES = -I$(top_srcdir)/include -I/usr/local/include/mysql
CPPFLAGS = -g -Wall
LDFLAGS = -L/usr/local/lib/mysql -L$(top_srcdir)/lib
LDADD = -lmysqlclient -ldb
bin_PROGRAMS = cdrwrap configwrap
cdrwrap_SOURCES = \
        cdrwrap.cc
configwrap_SOURCES = \
	configwrap.cc
