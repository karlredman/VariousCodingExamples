## include the README file
EXTRA_DIST = README

## override the 'all' target for the make
all:
	## link to the programs that are generated
	rm -rf ./test*
	ln -s $(top_builddir)/src/testC/testC .
	ln -s $(top_builddir)/src/testCC/testCC .

clean:
	rm -rf ./test*
