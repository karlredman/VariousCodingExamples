THISDIR=`pwd`

all:
#
# make the projects
	cd proj2; $(MAKE); cd ..;
	cd proj1; $(MAKE); cd ..;
	cd proj3; $(MAKE); cd ..;
#
# copy files into product packaging directory
	./copyfiles.sh;
#
# create spec file (not done)
######################
#
# create source tarball for packaging src (not done)
######################
#
# create packages
	rpm -ba verascape.spec

clean:
	cd proj2; $(MAKE) clean; cd ..;
	cd proj1; $(MAKE) clean; cd ..;
	cd proj3; $(MAKE) clean; cd ..;
