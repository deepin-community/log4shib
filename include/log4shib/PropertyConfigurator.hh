/*
 * SimpleConfigurator.hh
 *
 * Copyright 2001, Glen Scott. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */
#ifndef _LOG4SHIB_PROPERTYCONFIGURATOR_HH
#define _LOG4SHIB_PROPERTYCONFIGURATOR_HH

#include <log4shib/Portability.hh>
#include <log4shib/Export.hh>

#include <string>
#include <log4shib/Configurator.hh>	// configure exceptions

namespace log4shib {

    /**
       Property configurator will read a config file using the same (or similar)
       format to the config file used by log4j. This file is in a standard Java
       "properties" file format.
       <P>Example:<BR>
       <PRE>
       # a simple test config

       log4j.rootCategory=DEBUG, rootAppender
       log4j.category.sub1=A1
       log4j.category.sub2=INFO
       log4j.category.sub1.sub2=ERROR, A2
       
       log4j.appender.rootAppender=org.apache.log4j.ConsoleAppender
       log4j.appender.rootAppender.layout=org.apache.log4j.BasicLayout
       
       log4j.appender.A1=org.apache.log4j.FileAppender
       log4j.appender.A1.fileName=A1.log
       log4j.appender.A1.layout=org.apache.log4j.BasicLayout
       
       log4j.appender.A2=org.apache.log4j.ConsoleAppender
       log4j.appender.A2.layout=org.apache.log4j.PatternLayout
       log4j.appender.A2.layout.ConversionPattern=The message %%m at time %%d%%n
       </PRE>
       
       @since 0.3.2
    **/
    class LOG4SHIB_EXPORT PropertyConfigurator {
        public:
        static void configure(const std::string& initFileName);
    };
}

#endif // _LOG4SHIB_PROPERTYCONFIGURATOR_HH
