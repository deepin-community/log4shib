/*
 * RemoteSyslogAppender.cpp
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Walter Stroebel. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#include "PortabilityImpl.hh"

#ifdef LOG4SHIB_HAVE_UNISTD_H
# include <unistd.h>
#endif
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <log4shib/RemoteSyslogAppender.hh>
#include <sstream>
#ifdef WIN32
# include <winsock2.h>
# include <ws2tcpip.h>
#else
# include <netdb.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
#endif

using std::memcpy;

namespace log4shib {

    int RemoteSyslogAppender::toSyslogPriority(Priority::Value priority) {
        static int priorities[8] = { LOG_EMERG, LOG_ALERT, LOG_CRIT, LOG_ERR,
                                     LOG_WARNING, LOG_NOTICE, LOG_INFO, 
                                     LOG_DEBUG };
        int result;

        priority++;
        priority /= 100;

        if (priority < 0) {
            result = LOG_EMERG;
        } else if (priority > 7) {
            result = LOG_DEBUG;
        } else {
            result = priorities[priority];
        }

        return result;
    }
        

    RemoteSyslogAppender::RemoteSyslogAppender(const std::string& name, 
                                   const std::string& syslogName, 
                                   const std::string& relayer,
                                   int facility,
                                   int portNumber) :
        LayoutAppender(name),
        _syslogName(syslogName),
        _relayer(relayer),
        _facility((facility == -1) ? LOG_USER : facility),
        _portNumber((portNumber == -1) ? 514 : portNumber),
        _socket (0),
        _ipAddr (0)
#ifdef WIN32
        ,_cludge (0)
#endif
    {
        open();
    }
    
    RemoteSyslogAppender::~RemoteSyslogAppender() {
        close();
#ifdef WIN32
        if (_cludge) {
            // we started it, we end it.
            WSACleanup ();
        }
#endif
    }

    void RemoteSyslogAppender::open() {
        // Get a datagram socket.
        int type = SOCK_DGRAM;
#ifdef LOG4SHIB_HAVE_SOCK_CLOEXEC
        type |= SOCK_CLOEXEC;
#endif
        if ((_socket = socket(AF_INET, type, 0)) < 0) {
#ifdef WIN32
            if (WSAGetLastError () == WSANOTINITIALISED) {
                WSADATA wsaData;
                if (WSAStartup (0x101, &wsaData) != 0) {
                    return;
                }
                _cludge = 1;
                if ((_socket = socket(AF_INET, type, 0)) < 0) {
                    return;
                }
            } else {
                return; // fail silently
            }
#else
            return;
#endif
        }
#if !defined(LOG4SHIB_HAVE_SOCK_CLOEXEC) && defined(LOG4SHIB_HAVE_FD_CLOEXEC)
        int fdflags = ::fcntl(_socket, F_GETFD);
        if (fdflags != -1) {
            fdflags |= FD_CLOEXEC;
            ::fcntl(_socket, F_SETFD, fdflags);
        }
#endif
    }

    void RemoteSyslogAppender::close() {
        if (_socket) {
#ifdef WIN32
            closesocket (_socket);
#else
            ::close (_socket);
#endif
            _socket = 0;
        }
    }

    void RemoteSyslogAppender::_append(const LoggingEvent& event) {
        const std::string message(_getLayout().format(event));
        int messageLength = message.length();
        char *buf = new char [messageLength + 16];
        int priority = _facility + toSyslogPriority(event.priority);
        int preambleLength = sprintf (buf, "<%d>", priority);
        memcpy (buf + preambleLength, message.data(), messageLength);

        //convert int to str
        std::stringstream out;
        out << _portNumber;
        std::string port_str = out.str();

        const char *addr=_relayer.c_str();
        const char *port=port_str.c_str();

        //define addrinfo structure
        struct addrinfo *addrinf;
        if (getaddrinfo(addr, port, NULL, &addrinf) != 0) {
            delete[] buf;
            return;
        }

        while (messageLength > 0) {
            /* if packet larger than maximum (900 bytes), split
               into two or more syslog packets. */
            if (preambleLength + messageLength > 900) {
                sendto (_socket, buf, 900, 0, addrinf->ai_addr, addrinf->ai_addrlen);
                messageLength -= (900 - preambleLength);
                std::memmove (buf + preambleLength, buf + 900, messageLength);
            // note: we might need to sleep a bit here
            } else {
                sendto (_socket, buf, preambleLength + messageLength, 0, addrinf->ai_addr, addrinf->ai_addrlen);
                break;
            }
        }

        freeaddrinfo(addrinf);
        delete[] buf;
    }

    bool RemoteSyslogAppender::reopen() {
        close();
        open();
        return true;
    }

}
