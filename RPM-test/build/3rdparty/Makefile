all:
	cd GNU; $(MAKE); cd ..;
	cd v3p; $(MAKE); cd ..;
	rpm -ba 3rdparty.spec

clean:
	cd GNU; $(MAKE) clean; cd ..;
	cd v3p; $(MAKE) clean; cd ..;
