/*
 * CategoryStream.cpp
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "PortabilityImpl.hh"

#ifdef LOG4SHIB_HAVE_UNISTD_H
#    include <unistd.h>
#endif

#include <log4shib/CategoryStream.hh>
#include <log4shib/Category.hh>

namespace log4shib {

    CategoryStream::CategoryStream(Category& category, Priority::Value priority) :
        _category(category),
        _priority(priority),
        _buffer(NULL) {
    }

    CategoryStream::~CategoryStream() { 
        flush();
    }

    void CategoryStream::flush() {
        if (_buffer) {
            getCategory().log(getPriority(), _buffer->str());
            delete _buffer;
            _buffer = NULL;
        }
    }

    CategoryStream& CategoryStream::operator<< (cspf pf) {
 		return (*pf)(*this);
    }

    CategoryStream& eol (CategoryStream& os) {
        if  (os._buffer) {
    		os.flush();
        }
        return os;
    }
}
