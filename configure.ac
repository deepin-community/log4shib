AC_INIT(log4shib, 2.0.1)

# autoconf 2.50 or higher to rebuild aclocal.m4, because the
# AC_CREATE_PREFIX_CONFIG_H macro needs the AS_DIRNAME macro.
AC_PREREQ(2.50)

#
# +1 : ? : +1  == new interface that does not break old one
# +1 : ? : 0   == new interface that breaks old one
#  ? : ? : 0   == no new interfaces, but breaks apps
#  ? :+1 : ?   == just some internal changes, nothing breaks but might work 
#                 better
# CURRENT : REVISION : AGE
LT_VERSION=2:1:0

AC_SUBST(LT_VERSION)

#AC_CONFIG_SRCDIR(configure.in)
AC_CONFIG_AUX_DIR(config)
AC_CONFIG_HEADERS([include/config.h])
AX_PREFIX_CONFIG_H([include/log4shib/config.h])
AC_CONFIG_MACRO_DIR(m4)
AM_INIT_AUTOMAKE

# General "with" options
# ----------------------------------------------------------------------------
AC_ARG_WITH(idsa, AS_HELP_STRING(--with-idsa, [include idsa support]),)

# Checks for programs
# ----------------------------------------------------------------------------
AC_CANONICAL_HOST

AC_ARG_ENABLE(debug,
    AS_HELP_STRING(--enable-debug, [Produce debug variant (Default = no)]),
    enable_debug=$enableval, enable_debug=no)

if test "$enable_debug" = "yes" ; then
    AM_CFLAGS="-D_DEBUG"
    AM_CXXFLAGS="-D_DEBUG"
fi

LT_INIT([disable-static])
AC_PROG_INSTALL
AC_PROG_MAKE_SET

AC_PROG_CXX([g++ c++ gpp aCC CC cxx cc++ cl FCC KCC RCC xlC_r xlC QCC])

if test "$GCC" = "yes" ; then
    AM_CFLAGS="$AM_CFLAGS -Wall -W"
    AM_CXXFLAGS="$AM_CXXFLAGS -Wall -W"
fi

AC_PROG_CXXCPP
AC_LANG(C)

# Checks header files
# ----------------------------------------------------------------------------
AC_CHECK_HEADERS([unistd.h])
AC_CHECK_HEADERS([io.h])


# Checks close-on-exec functionality
# ----------------------------------------------------------------------------
AC_CHECK_DECL([O_CLOEXEC],
        [AC_DEFINE([HAVE_O_CLOEXEC],[1],[Define to 1 if open supports O_CLOEXEC flag.])],,
        [#include <fcntl.h>])
AC_CHECK_DECL([FD_CLOEXEC],
        [AC_DEFINE([HAVE_FD_CLOEXEC],[1],[Define to 1 if fcntl supports FD_CLOEXEC flag.])],,
        [#include <fcntl.h>])
AC_CACHE_CHECK([for SOCK_CLOEXEC support], [log_cv_sock_cloexec],
[AC_TRY_RUN([
#include <sys/types.h>
#include <sys/socket.h>
int main()
{
return socket(AF_INET, SOCK_STREAM|SOCK_CLOEXEC, 0) == -1;
}], [log_cv_sock_cloexec=yes], [log_cv_sock_cloexec=no], [log_cv_sock_cloexec=no])])

if test "$log_cv_sock_cloexec" = "yes"; then
	AC_DEFINE([HAVE_SOCK_CLOEXEC], 1, [Define if the SOCK_CLOEXEC flag is supported])
fi


# Checks local idioms
# ----------------------------------------------------------------------------
AC_C_INT64_T
AC_FUNC_SNPRINTF
AC_CHECK_FUNCS([syslog gettimeofday ftime localtime_r gmtime_r])

# Checks for libraries
# ----------------------------------------------------------------------------

# for RemoteSyslogAppender
AC_SEARCH_LIBS([socket],[socket],,[AC_MSG_ERROR([cannot find socket() function])])
AC_SEARCH_LIBS([gethostbyname],[nsl],,[AC_MSG_ERROR([cannot find gethostbyname() function])])

AX_PTHREAD(
   [AC_DEFINE(HAVE_THREADING,1,[define if threading is enabled])
    AC_DEFINE(USE_PTHREADS,1,[define if pthread library is available])
    AC_DEFINE(_PTHREADS,1,[define for STL if pthread library is used])
    AM_CFLAGS="$PTHREAD_CFLAGS $AM_CFLAGS"
    AM_CXXFLAGS="$PTHREAD_CFLAGS $AM_CXXFLAGS"
    CC="$PTHREAD_CC"],
   [AC_MSG_ERROR([unable to find pthreads, currently this is required])])

AC_SUBST([AM_CFLAGS])
AC_SUBST([AM_CXXFLAGS])

AC_LANG(C++)

AC_CXX_HAVE_SSTREAM

# idsa_test
if test "x$with_idsa" = xyes; then
    AC_CHECK_LIB([idsa], [idsa_open],)
    if test "$ac_cv_lib_idsa_idsa_open" = no; then
        AC_MSG_ERROR([could not locate idsa library])
    fi
fi

# check for doxygen
# ----------------------------------------------------------------------------
BB_ENABLE_DOXYGEN

# Create files
# ----------------------------------------------------------------------------

AC_CONFIG_FILES([
Makefile
log4shib.spec
log4shib.pc
Portfile
doc/Makefile
doc/Doxyfile
doc/html/Makefile
src/Makefile
include/Makefile
include/log4shib/Makefile
include/log4shib/threading/Makefile
tests/Makefile
])
AC_OUTPUT
