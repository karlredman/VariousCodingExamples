## include the README file
EXTRA_DIST = README

## override the 'all' target for the make
all:
	## link to the programs that are generated
	rm -rf ./test* producer consumer cdrwrap configwrap
	ln -s $(top_builddir)/src/testC/testC .
	ln -s $(top_builddir)/src/testCC/testCC .

	ln -s $(top_builddir)/src/producer/producer .
	ln -s $(top_builddir)/src/consumer/consumer .
	ln -s $(top_builddir)/src/cdwraptest/cdrwrap .
	ln -s $(top_builddir)/src/cdwraptest/configwrap .

clean:
	rm -rf ./test*
