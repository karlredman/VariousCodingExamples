#
# Spec file for Veraserv product
#
Name: veraserv
Summary: Verascape veraserv products
Version: 0.90
Release: 2
Copyright: Verascape, Inc. 2001
Group: Applications/verascape/veraserv
#Source: proj1

Distribution: veraserv
Vendor: Veriscape, Inc.
Packager: Verascape Build Master
%description
veraserv products 

arch_compat: i386: i486: i586
os_compat: Linux : Solaris

##########################
%prep
#rm -rf $RPM_BUILD_DIR/proj1
#zcat $RPM_SOURCE_DIR/proj1-0.95.tgz | tar -xvf -
#%setup

%build
#make

%install
#make install

#####################
%ifos Linux
%package proj1
Summary: Verascape veraserv project 1
Group: Applications/verascape/veraserv

Version: 0.90
Release: 2

%description proj1
proj1 of RPM-test for verascape packaging tests. Uses verascape and GNU mock libs. 
Don't forget to set you LD_LIBRARY_PATH to /opt/sfw/lib, /opt/v3p/lib, and 
/opt/verascape/lib!

%files proj1
%attr (750, veraserv, users) /opt/verascape/bin/proj1

%endif

#####################
%package proj2
Summary: Verascape veraserv project 2
Group: Applications/verascape/veraserv

Version: 0.95
Release: 2

%description proj2
proj2 of RPM-test for verascape packaging tests. Uses verascape and GNU mock libs. 
Don't forget to set you LD_LIBRARY_PATH to /opt/sfw/lib, /opt/v3p/lib, and 
/opt/verascape/lib!

Conflicts: %{name}-proj2 <= 0.90-1
#Conflicts: proj2 <= 0.90-1

%files proj2
%attr (660, veraserv, users) /opt/verascape/lib/libVruntime.so
%attr (660, veraserv, users) /opt/verascape/lib/libVstatic.a

#####################
%ifos solaris
%package proj3
Summary: Verascape veraserv project 3
Group: Applications/verascape/veraserv

Version: 0.91
Release: 3

%description proj3
proj3 of RPM-test for verascape packaging tests. Uses verascape and GNU mock libs. 
Don't forget to set you LD_LIBRARY_PATH to /opt/sfw/lib, /opt/v3p/lib, and 
/opt/verascape/lib!

Conflicts: %{name} <= 0.90-1

%files proj3
%attr (750, veraserv, users) /opt/verascape/bin/proj3
%endif
