/*
 * BasicLayout.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "PortabilityImpl.hh"
#include <log4shib/BasicLayout.hh>
#include <log4shib/Priority.hh>
#ifdef LOG4SHIB_HAVE_SSTREAM
#include <sstream>
#endif

namespace log4shib {

    BasicLayout::BasicLayout() {
    }
    
    BasicLayout::~BasicLayout() {
    }

    std::string BasicLayout::format(const LoggingEvent& event) {
        std::ostringstream message;

        const std::string& priorityName = Priority::getPriorityName(event.priority);
        message << event.timeStamp.getSeconds() << " " << priorityName << " " 
                << event.categoryName << " " << event.ndc << ": " 
                << event.message << std::endl;

        return message.str();
    }
}
