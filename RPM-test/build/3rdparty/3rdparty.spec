#
# Spec file for Veraserv product
#
Name: 3rdparty
Summary: mock 3rdparty software libs
Version: 0.1
Release: 1
Copyright: various
Group: Applications/verascape/veraserv
Vendor: various
Packager: Verascape Build Master
%description
3rd party packages

%prep

%build

%install

%package v3p
Summary: Verascape veraserv project 1
Copyright: GNU
Distribution: GNU
Group: Applications/verascape/3rdparty
%description v3p
mock libraries for mock veraserv products from GNU

%package GNU
Summary: Verascape veraserv project 2
Copyright: Some Company, Inc. 2001
Distribution: some company package
Group: Applications/verascape/3rdparty
%description GNU
mock libraries for mock veraserv products from vendors


%files v3p
/opt/v3p/lib

%files GNU
/opt/sfw/lib
