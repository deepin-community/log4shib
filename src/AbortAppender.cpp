/*
 * AbortAppender.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "PortabilityImpl.hh"
#include <log4shib/AbortAppender.hh>
#include <cstdlib>

namespace log4shib {

    AbortAppender::AbortAppender(const std::string& name) : 
        AppenderSkeleton(name) {
    }
    
    AbortAppender::~AbortAppender() {
        close();
    }

    void AbortAppender::close() {
        // empty
    }

    void AbortAppender::_append(const LoggingEvent&) {
        std::abort();
    }

    bool AbortAppender::reopen() {
        return true;
    }
      
    bool AbortAppender::requiresLayout() const {
        return false;
    }

    void AbortAppender::setLayout(Layout*) {
        return;
    }
}
