Name:           linearalgebracpp-devel
Version:        %{package_version}
Release:        1
Summary:        Header-only C++ linear algebra library
License:        MIT
URL:            https://github.com/fangface-hub/LinearAlgebraCpp
Source0:        linearalgebracpp-%{version}.tar.gz
BuildArch:      noarch

%description
A readable C++11 template library for matrices and vectors.

%prep
%setup -q -n linearalgebracpp-%{version}

%build

%install
install -d %{buildroot}/usr/local/include
install -m 644 Include/Matrix.h Include/RowVector.h Include/ColVector.h \
    %{buildroot}/usr/local/include/

%files
%license LICENSE
/usr/local/include/Matrix.h
/usr/local/include/RowVector.h
/usr/local/include/ColVector.h
