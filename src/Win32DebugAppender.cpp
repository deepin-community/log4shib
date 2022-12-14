/*
 * Win32DebugAppender.cpp
 *
 * Copyright 2002, the Log4cpp project.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifdef WIN32	// only available on Win32

#include "PortabilityImpl.hh"
#ifdef LOG4SHIB_HAVE_IO_H
#    include <io.h>
#endif

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winbase.h>

#include <stdio.h>
#include "log4shib/Category.hh"
#include "log4shib/Win32DebugAppender.hh"

namespace log4shib {

    Win32DebugAppender::Win32DebugAppender(const std::string& name) : 
            LayoutAppender(name) {
    }
    
    Win32DebugAppender::~Win32DebugAppender() {
        close();
    }

    void Win32DebugAppender::close() {
    }

    void Win32DebugAppender::_append(const LoggingEvent& event) {
        std::string message(_getLayout().format(event));
		::OutputDebugString(message.c_str());
    }
}

#endif	// WIN32
