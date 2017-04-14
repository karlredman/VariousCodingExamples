THISDIR = `pwd`

all:
	cd /opt/sfw; $(MAKE); cd $(THISDIR);
	cd /opt/v3p; $(MAKE); cd $(THISDIR);
	cd /opt/verascape; $(MAKE); cd $(THISDIR);
	cd 3rdparty; $(MAKE); cd ..;
	cd veraserv; $(MAKE); cd ..;

clean:
	cd /opt/sfw; $(MAKE) clean; cd $(THISDIR);
	cd /opt/v3p; $(MAKE) clean; cd $(THISDIR);
	cd /opt/verascape; $(MAKE) clean; cd $(THISDIR);
	cd 3rdparty; $(MAKE) clean; cd ..;
	cd veraserv; $(MAKE) clean; cd ..;
