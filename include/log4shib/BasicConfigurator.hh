/*
 * BasicConfigurator.hh
 *
 * Copyright 2002, Log4cpp Project. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */
#ifndef _LOG4SHIB_BASICCONFIGURATOR_HH
#define _LOG4SHIB_BASICCONFIGURATOR_HH

#include <log4shib/Portability.hh>

namespace log4shib {

    /**
       This class implements a trivial default configuration for log4shib:
       it adds a FileAppender that logs to stdout and uses a BasicLayout to
       the root Category.
       @since 0.3.2
     **/
    class LOG4SHIB_EXPORT BasicConfigurator {
    public:

        /**
           Performs a minimal configuration of log4shib.  
         **/
        static void configure();
 };
}

#endif
