## include the README file
EXTRA_DIST = README

## override the 'all' target for the make
all:
	## link to the programs that are generated
	rm -rf ./timertest*
	ln -s $(top_builddir)/src/timers/timertest .
	ln -s $(top_builddir)/src/timers1/timertest1 .
	ln -s $(top_builddir)/src/timers2/timertest2 .
	ln -s $(top_builddir)/src/timers3/timertest3 .

clean:
	rm -rf ./timertest*
