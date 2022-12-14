/*
 * Portability.hh
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4SHIB_PORTABILITY_HH
#define _LOG4SHIB_PORTABILITY_HH

#if defined (_MSC_VER) || defined(__BORLANDC__)
#    if defined (LOG4SHIB_STLPORT_AND_BOOST_BUILD)
#        include <log4shib/config-win32-stlport-boost.h>
#    else
#        include <log4shib/config-win32.h>
#    endif
#else
#if defined(__OPENVMS__)
#    include <log4shib/config-openvms.h>
#else
#    include <log4shib/config.h>
#endif
#endif

#include <log4shib/Export.hh>

#if defined(_MSC_VER)
#    pragma warning( disable : 4786 ) // 255 char debug symbol limit
#    pragma warning( disable : 4290 ) // throw specifier not implemented
#    pragma warning( disable : 4251 ) // "class XXX should be exported"
#endif

#ifndef LOG4SHIB_HAVE_SSTREAM
#include <strstream>
namespace std {
    class LOG4SHIB_EXPORT ostringstream : public ostrstream {
        public:
        std::string str();
    };
}
#endif

#endif
