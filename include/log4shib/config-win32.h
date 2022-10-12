#ifndef _INCLUDE_LOG4SHIB_CONFIG_WIN32_H
#define _INCLUDE_LOG4SHIB_CONFIG_WIN32_H 1

/* manually edited from include/log4shib/config.h */

/* Define if you have the syslog function.  */
/* #undef LOG4SHIB_HAVE_SYSLOG */

/* Define if you have the `ftime' function. */
#ifndef LOG4SHIB_HAVE_FTIME
#define LOG4SHIB_HAVE_FTIME  1
#endif

/* Define if you have the `gettimeofday' function. */
/* #undef LOG4SHIB_HAVE_GETTIMEOFDAY */

/* define if the compiler has int64_t */
#ifndef LOG4SHIB_HAVE_INT64_T
#define LOG4SHIB_HAVE_INT64_T
#define int64_t __int64


#if defined(_MSC_VER) && _MSC_VER < 1300
#define LOG4SHIB_MISSING_INT64_OSTREAM_OP
#endif

#endif

/* define if the compiler has in_addr_t */
#ifndef LOG4SHIB_HAVE_IN_ADDR_T
#define LOG4SHIB_HAVE_IN_ADDR_T

#ifndef u_long
typedef unsigned long u_long;
#endif

/* u_long is the type of in_addr.s_addr */
typedef u_long in_addr_t;

/* u_short is the type of sockaddr_in.sin_port */
// typedef u_short		in_port_t;

#endif


/* Define if you have the <io.h> header file.  */
#ifndef LOG4SHIB_HAVE_IO_H
#define LOG4SHIB_HAVE_IO_H 1
#endif

/* Define if you have the <unistd.h> header file.  */
/* #undef LOG4SHIB_HAVE_UNISTD_H */

/* Define if you have the idsa library (-lidsa).  */
/* #undef LOG4SHIB_HAVE_LIBIDSA */

/* Define if you have the `strcasecmp' function. */
/* #undef LOG4SHIB_HAVE_STRCASECMP */

/* Name of package */
#ifndef LOG4SHIB_PACKAGE
#define LOG4SHIB_PACKAGE  "log4shib"
#endif

/* Version number of package */
#ifndef LOG4SHIB_VERSION
#define LOG4SHIB_VERSION  "2.0.1"
#endif

/* define if the compiler implements namespaces */
#ifndef LOG4SHIB_HAVE_NAMESPACES
#define LOG4SHIB_HAVE_NAMESPACES 1
#endif

/* define if the compiler has stringstream */
#ifndef LOG4SHIB_HAVE_SSTREAM
#define LOG4SHIB_HAVE_SSTREAM 1
#endif

/* define if the C library has snprintf */
#ifndef LOG4SHIB_HAVE_SNPRINTF
#define LOG4SHIB_HAVE_SNPRINTF 1
#endif

/* define to get around problems with ERROR in windows.h */
#ifndef LOG4SHIB_FIX_ERROR_COLLISION
#define LOG4SHIB_FIX_ERROR_COLLISION 1
#endif

/* define WIN32 for Borland */
#ifndef WIN32
#define WIN32
#endif

/* use threads */
#ifndef LOG4SHIB_HAVE_THREADING
#define LOG4SHIB_HAVE_THREADING
#endif

/* use ms threads */
#ifndef LOG4SHIB_USE_MSTHREADS
#define LOG4SHIB_USE_MSTHREADS
#endif

/* supply DLL main */
#ifndef LOG4SHIB_SUPPLY_DLLMAIN
#define LOG4SHIB_SUPPLY_DLLMAIN
#endif

/* MSVCs <cstdlib> and <cstring> headers are broken in the sense that they
   put functions in the global namespace instead of std::
   The #defines below enable a workaround for MSVC 6 and lower. If MSVC 7
   is still broken please adjust the _MSC_VER version check and report it.
   See also bug report #628211.
*/
#if defined(_MSC_VER) && _MSC_VER < 1300

#ifndef LOG4SHIB_CSTDLIB_NOT_IN_STD
#define LOG4SHIB_CSTDLIB_NOT_IN_STD
#endif

#ifndef LOG4SHIB_CSTRING_NOT_IN_STD
#define LOG4SHIB_CSTRING_NOT_IN_STD
#endif

#ifndef LOG4SHIB_CTIME_NOT_IN_STD
#define LOG4SHIB_CTIME_NOT_IN_STD
#endif

#ifndef LOG4SHIB_CMATH_NOT_IN_STD
#define LOG4SHIB_CMATH_NOT_IN_STD
#endif

#endif

/* define mode_t. Move to Portability.hh if more platforms need it */
typedef int mode_t;

#define _CRT_SECURE_NO_DEPRECATE 1
#define _CRT_NONSTDC_NO_DEPRECATE 1

/* _INCLUDE_LOG4SHIB_CONFIG_WIN32_H */
#endif
