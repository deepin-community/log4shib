/*
 * FileAppender.cpp
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "PortabilityImpl.hh"
#ifdef LOG4SHIB_HAVE_IO_H
#    include <io.h>
#endif
#ifdef LOG4SHIB_HAVE_UNISTD_H
#    include <unistd.h>
#endif

#include <fcntl.h>
#include <stdio.h>
#include <time.h>
#include <log4shib/FileAppender.hh>
#include <log4shib/Category.hh>

namespace log4shib {

    FileAppender::FileAppender(const std::string& name, 
                               const std::string& fileName,
                               bool append,
                               mode_t mode) : 
            LayoutAppender(name),
            _fileName(fileName),
            _flags(O_CREAT | O_APPEND | O_WRONLY),
            _mode(mode) {
        if (!append)
            _flags |= O_TRUNC;
#ifdef LOG4SHIB_HAVE_O_CLOEXEC
        _flags |= O_CLOEXEC;
#endif
        _fd = ::open(_fileName.c_str(), _flags, _mode);
        if (_fd == -1)
            throw std::runtime_error(std::string("failed to open log file (") + _fileName + ')');
#if !defined(LOG4SHIB_HAVE_O_CLOEXEC) && defined(LOG4SHIB_HAVE_FD_CLOEXEC)
        int fdflags = ::fcntl(_fd, F_GETFD);
        if (fdflags != -1) {
            fdflags |= FD_CLOEXEC;
            ::fcntl(_fd, F_SETFD, fdflags);
        }
#endif
    }
    
    FileAppender::FileAppender(const std::string& name, int fd) :
        LayoutAppender(name),
        _fileName(""),
        _fd(fd),
        _flags(O_CREAT | O_APPEND | O_WRONLY),
        _mode(00644) {
#ifdef LOG4SHIB_HAVE_O_CLOEXEC
        _flags |= O_CLOEXEC;
#endif
#if !defined(LOG4SHIB_HAVE_O_CLOEXEC) && defined(LOG4SHIB_HAVE_FD_CLOEXEC)
        int fdflags = ::fcntl(_fd, F_GETFD);
        if (fdflags != -1) {
            fdflags |= FD_CLOEXEC;
            ::fcntl(_fd, F_SETFD, fdflags);
        }
#endif
    }
    
    FileAppender::~FileAppender() {
        close();
    }

    void FileAppender::close() {
        if (_fd != -1) {
            ::close(_fd);
            _fd = -1;
        }
    }

    void FileAppender::setAppend(bool append) {
        if (append) {
            _flags &= ~O_TRUNC;
        } else {
            _flags |= O_TRUNC;
        }
    }

    bool FileAppender::getAppend() const {
        return (_flags & O_TRUNC) == 0;
    }

    void FileAppender::setMode(mode_t mode) {
        _mode = mode;
    }

    mode_t FileAppender::getMode() const {
        return _mode;
    }

    void FileAppender::_append(const LoggingEvent& event) {
        if (_fd != -1) {
            std::string message(_getLayout().format(event));
            if (!::write(_fd, message.data(), message.length())) {
                // XXX help! help!
            }
        }
    }

    bool FileAppender::reopen() {
        if (_fileName != "") {
            int fd = ::open(_fileName.c_str(), _flags, _mode);
            if (fd < 0)
                return false;
            else {
                if (_fd != -1)
                    ::close(_fd);
                _fd = fd;
#if !defined(LOG4SHIB_HAVE_O_CLOEXEC) && defined(LOG4SHIB_HAVE_FD_CLOEXEC)
                int fdflags = ::fcntl(_fd, F_GETFD);
                if (fdflags != -1) {
                    fdflags |= FD_CLOEXEC;
                    ::fcntl(_fd, F_SETFD, fdflags);
                }
#endif
                return true;
            }
        } else {
            return true;
        }      
    }
}
