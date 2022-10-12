Name:       log4shib
Version:    2.0.1
Release:    1
Summary:    Log for C++, Shibboleth Edition
License:    LGPL
Group:      Development/Libraries
Vendor:     Shibboleth Consortium
URL:        http://shibboleth.net/downloads/log4shib/2.0.1
Source:     %name-%version.tar.bz2
BuildRoot:  %_tmppath/%name-%version-root
BuildRequires:  gcc-c++ pkgconfig
%{!?_without_doxygenrpm:BuildRequires: doxygen}
%if "%{_vendor}" == "redhat"  
BuildRequires: redhat-rpm-config  
%endif  

%if 0%{?rhel} >= 8 || 0%{?centos_version} >= 800
BuildRequires: gdb
%endif

%if "%{_vendor}" == "suse"
%define pkgdocdir %{_docdir}/%{name}
%else
%define pkgdocdir %{_docdir}/%{name}-%{version}
%endif

%description
Log for C++ is a library of classes for flexible logging to files, syslog,
and other destinations. It is modeled after the Log for Java library and
stays as close to its API as is reasonable.

%package -n liblog4shib2
Summary:    Log for C++, Shibboleth Edition
Group:      Development/Libraries
Provides:   log4shib = %{version}-%{release}
Obsoletes:  log4shib < %{version}-%{release}

%description -n liblog4shib2
Log for C++ is a library of classes for flexible logging to files, syslog,
and other destinations. It is modeled after the Log for Java library and
stays as close to its API as is reasonable.

This package contains just the shared library.

%package -n liblog4shib-devel
Summary: Development tools for Log for C++
Group: Development/Libraries
Requires:   liblog4shib2 = %{version}-%{release}
Provides:	log4shib-devel = %{version}-%{release}
Obsoletes:  log4shib-devel < %{version}-%{release}

%description -n liblog4shib-devel
The static libraries and header files needed for development with log4shib.

%prep
%setup -q

%build
%configure %{!?_without_doxygenrpm:--enable-doxygen} %{?_without_doxygenrpm:--disable-doxygen}
%{__make}

%install
%{__make} DESTDIR=$RPM_BUILD_ROOT apidir=$RPM_BUILD_ROOT%{pkgdocdir}/api install
# If we use %doc down below to package the README files from the build tree,
# it will blow away the package's docdir folder, and the installed API docs with it.
# Instead, copy the README files manually into the platform's docdir.
config/install-sh -d $RPM_BUILD_ROOT%{pkgdocdir}
config/install-sh -m 644 -c AUTHORS COPYING INSTALL NEWS README THANKS ChangeLog $RPM_BUILD_ROOT%{pkgdocdir}

%clean
[ "$RPM_BUILD_ROOT" != "/" ] && %{__rm} -rf $RPM_BUILD_ROOT

%post -n liblog4shib2 -p /sbin/ldconfig

%post -n liblog4shib-devel
if test "x$RPM_INSTALL_PREFIX0" != "x" ; then
    %{__perl} -pi -e"s|^prefix=\"[^\"]*\"|prefix=\"$RPM_INSTALL_PREFIX0\"|" $RPM_INSTALL_PREFIX0/bin/log4shib-config
fi

%postun -n liblog4shib2 -p /sbin/ldconfig

%files -n liblog4shib2
%defattr(-,root,root,755)
%attr(755,root,root) %{_libdir}/lib*.so.*

%files -n liblog4shib-devel
%defattr(-,root,root,755)
%{_includedir}/*
%{!?_without_doxygenrpm:%{_mandir}/man?/*}
%attr(755,root,root) %{_libdir}/*.so
%attr(644,root,root) %{_libdir}/*.a
%attr(644,root,root) %{_libdir}/pkgconfig/log4shib.pc
%exclude %{_libdir}/*.la
%doc %{pkgdocdir}

%changelog
* Fri Sep 27 2019 Scott Cantor <cantor.2@osu.edu> - 2.0.0-2
- Remove old Solaris exclusions
- Add CentOS 8 gdb dependency

* Mon Jun 25 2018 Scott Cantor <cantor.2@osu.edu> - 2.0.0-1
- Bump version
- Switch to bzipped source

* Thu May 23 2013  Scott Cantor  <cantor.2@osu.edu>  - 1.0.6-1
- Patch to limit file handle leakage from prop-based configs

* Sat Jul 21 2012  Scott Cantor  <cantor.2@osu.edu>  - 1.0.5-1
- Fix Provides/Obsoletes versioning
- Update Vendor and URL

* Mon Dec 28 2009  Scott Cantor  <cantor.2@osu.edu>  - 1.0.4-1
- Sync package naming to support side by side installs

* Sat Oct 24 2009  Scott Cantor  <cantor.2@osu.edu>  - 1.0.3-2
- Cleaned up specfile for OpenSUSE build service

* Wed Aug 5 2009  Scott Cantor  <cantor.2@osu.edu>  - 1.0.3-1
- Cleaned up specfile for OpenSUSE build service
