/*
 * RollingFileAppender.cpp
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

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <log4shib/RollingFileAppender.hh>
#include <log4shib/Category.hh>
#ifdef LOG4SHIB_HAVE_SSTREAM
#include <sstream>
#endif

namespace log4shib {

    RollingFileAppender::RollingFileAppender(const std::string& name,
                                             const std::string& fileName, 
                                             size_t maxFileSize, 
                                             unsigned int maxBackupIndex,
                                             bool append,
                                             mode_t mode) :
        FileAppender(name, fileName, append, mode),
        _maxBackupIndex(maxBackupIndex),
        _maxFileSize(maxFileSize) {
    }

    void RollingFileAppender::setMaxBackupIndex(unsigned int maxBackups) { 
        _maxBackupIndex = maxBackups; 
    }
    
    unsigned int RollingFileAppender::getMaxBackupIndex() const { 
        return _maxBackupIndex; 
    }

    void RollingFileAppender::setMaximumFileSize(size_t maxFileSize) {
        _maxFileSize = maxFileSize;
    }

    size_t RollingFileAppender::getMaxFileSize() const { 
        return _maxFileSize; 
    }

    void RollingFileAppender::rollOver() {
        if (_fd != -1)
            ::close(_fd);
        if (_maxBackupIndex > 0) {
            std::ostringstream oldName;
            oldName << _fileName << "." << _maxBackupIndex << std::ends;
            ::remove(oldName.str().c_str());
            size_t n = _fileName.length() + 1;
            for(unsigned int i = _maxBackupIndex; i > 1; i--) {
            	std::string newName = oldName.str();
#ifndef LOG4SHIB_STLPORT_AND_BOOST_BUILD
                oldName.seekp(n, std::ios::beg);
#else
				// the direction parameter is broken in STLport 4.5.3, 
				// so we don't specify it (the code works without it)
				oldName.seekp(n);
#endif
                oldName << i-1 << std::ends;
                ::rename(oldName.str().c_str(), newName.c_str());
            }
            ::rename(_fileName.c_str(), oldName.str().c_str());
        }
        _fd = ::open(_fileName.c_str(), _flags, _mode);
#if !defined(LOG4SHIB_HAVE_O_CLOEXEC) && defined(LOG4SHIB_HAVE_FD_CLOEXEC)
        int fdflags = ::fcntl(_fd, F_GETFD);
        if (fdflags != -1) {
            fdflags |= FD_CLOEXEC;
            ::fcntl(_fd, F_SETFD, fdflags);
        }
#endif
    }

    void RollingFileAppender::_append(const LoggingEvent& event) {
        FileAppender::_append(event);
        off_t offset = -1;
        if (_fd != -1)
            offset = ::lseek(_fd, 0, SEEK_END);
        if (offset < 0) {
            // XXX we got an error, ignore for now
        } else {
            if(static_cast<size_t>(offset) >= _maxFileSize) {
                rollOver();
            }
        }
    }
}
