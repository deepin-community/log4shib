// testNTEventLog.cpp : Derived from testPattern.cpp.
//

#include "log4shib/Portability.hh"
#include "log4shib/NTEventLogAppender.hh"

#ifdef LOG4SHIB_HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <stdlib.h>

#include "log4shib/Category.hh"
#include "log4shib/Appender.hh"
#include "log4shib/NTEventLogAppender.hh"
#include "log4shib/Priority.hh"

int main(int argc, char* argv[])
{
    log4shib::Appender* appender = 
        new log4shib::NTEventLogAppender("default", "testNTEventLog");

    log4shib::Category& sub1 = 
        log4shib::Category::getInstance(std::string("sub1"));
    sub1.addAppender(appender);
    sub1.setPriority(log4shib::Priority::DEBUG);
    
    sub1.emerg("sub1 emerg");
    sub1.fatal("sub1 fatal");
    sub1.alert("sub1 alert");
    sub1.crit("sub1 crit");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");
    sub1.notice("sub1 notice");
    sub1.info("sub1 info");
    sub1.debug("sub1 debug");
    sub1.log(log4shib::Priority::NOTSET, "sub1 notset");
    sub1.log(log4shib::Priority::ERROR, "sub1 error");

    log4shib::Category::shutdown();

    return 0;
}

