## include the README file
EXTRA_DIST = README

## override the 'all' target for the make
all:
	## link to the programs that are generated
	rm -rf ./test*
	rm -rf ./expect*
	ln -s $(top_builddir)/src/test/test1 .
	ln -s $(top_builddir)/src/test/test2 .
	ln -s $(top_builddir)/src/test/test3 .
	#chmod 750 $(top_builddir)/scripts/expect_script
	#chmod 750 $(top_builddir)/scripts/watch_script
	ln -s $(top_builddir)/scripts/expect_script .
	ln -s $(top_builddir)/scripts/watch_script .

clean:
	rm -rf ./test*
	rm -rf ./expect*
