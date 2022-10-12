#ifndef _LOG4SHIB_EXPORT_HH
#define _LOG4SHIB_EXPORT_HH

#ifdef LOG4SHIB_HAS_DLL
#	ifdef LOG4SHIB_BUILD_DLL
#		define LOG4SHIB_EXPORT __declspec(dllexport)
#	else
#		define LOG4SHIB_EXPORT __declspec(dllimport)
#	endif
#else
#	define LOG4SHIB_EXPORT 
#endif

#endif // _LOG4SHIB_EXPORT_HH

