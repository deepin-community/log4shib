/*
 * SimpleLayout.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4SHIB_SIMPLELAYOUT_HH
#define _LOG4SHIB_SIMPLELAYOUT_HH

#include <log4shib/Portability.hh>
#include <log4shib/Layout.hh>

namespace log4shib {
    
    /**
     * BasicLayout is a simple fixed format Layout implementation. 
     **/
    class LOG4SHIB_EXPORT SimpleLayout : public Layout {
        public:
        SimpleLayout();
        virtual ~SimpleLayout();

        /**
         * Formats the LoggingEvent in SimpleLayout style:<br>
         * "priority - message"
         **/
        virtual std::string format(const LoggingEvent& event);
    };        
}

#endif // _LOG4SHIB_SIMPLELAYOUT_HH
