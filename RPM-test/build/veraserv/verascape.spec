#
# Spec file for Veraserv product
#
Name: veraserv
Summary: Verascape veraserv products
Version: 0.90
Release: 1
Copyright: Verascape, Inc. 2001
Group: Applications/verascape/veraserv
#Source: proj1
Distribution: veraserv
Vendor: Veriscape, Inc.
Packager: Verascape Build Master
%description
veraserv products 

%prep
#rm -rf $RPM_BUILD_DIR/proj1
#zcat $RPM_SOURCE_DIR/proj1-0.95.tgz | tar -xvf -
#%setup

%build
#make

%install
#make install

%package proj1
Summary: Verascape veraserv project 1
Group: Applications/verascape/veraserv
%description proj1
proj1 of RPM-test for verascape packaging tests. Uses verascape and GNU mock libs. 
Don't forget to set you LD_LIBRARY_PATH to /opt/sfw/lib, /opt/v3p/lib, and 
/opt/verascape/lib!

%package proj2
Summary: Verascape veraserv project 2
Group: Applications/verascape/veraserv
%description proj2
proj2 of RPM-test for verascape packaging tests. Uses verascape and GNU mock libs. 
Don't forget to set you LD_LIBRARY_PATH to /opt/sfw/lib, /opt/v3p/lib, and 
/opt/verascape/lib!


%package proj3
Summary: Verascape veraserv project 3
Group: Applications/verascape/veraserv
%description proj3
proj3 of RPM-test for verascape packaging tests. Uses verascape and GNU mock libs. 
Don't forget to set you LD_LIBRARY_PATH to /opt/sfw/lib, /opt/v3p/lib, and 
/opt/verascape/lib!

%files proj1
/opt/verascape/bin/proj1

%files proj2
/opt/verascape/lib/libVruntime.so
/opt/verascape/lib/libVstatic.a

%files proj3
/opt/verascape/bin/proj3
