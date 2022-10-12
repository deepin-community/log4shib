/*
 * SimpleConfigurator.cpp
 *
 * Copyright 2001, Glen Scott. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */
#include "PortabilityImpl.hh"

#ifdef LOG4SHIB_HAVE_UNISTD_H
#include <unistd.h>
#endif
#ifdef LOG4SHIB_HAVE_IO_H
#    include <io.h>
#endif

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>

#include <log4shib/Category.hh>
#include <log4shib/Appender.hh>
#include <log4shib/OstreamAppender.hh>
#include <log4shib/FileAppender.hh>
#include <log4shib/RollingFileAppender.hh>
#include <log4shib/Layout.hh>
#include <log4shib/BasicLayout.hh>
#include <log4shib/SimpleLayout.hh>
#include <log4shib/Priority.hh>
#include <log4shib/NDC.hh>
#include <log4shib/PatternLayout.hh>
#include <log4shib/SimpleConfigurator.hh>
#if LOG4SHIB_HAVE_SYSLOG
#include <log4shib/SyslogAppender.hh>
#endif
#include <log4shib/RemoteSyslogAppender.hh>
#ifdef WIN32
#include <log4shib/NTEventLogAppender.hh>
#endif

namespace log4shib {

    void SimpleConfigurator::configure(const std::string& initFileName) {
        std::ifstream initFile(initFileName.c_str());
        
        if (!initFile) {
            throw ConfigureFailure(std::string("Config File ") + initFileName + " does not exist or is unreadable");
        }
        
        configure(initFile);
    }
          
    void SimpleConfigurator::configure(std::istream& initFile) {
        std::string nextCommand;
        std::string categoryName;
        
        while (initFile >> nextCommand) {
            /* skip comment lines */
            if (nextCommand[0] == '#') {
                std::string dummy;
                std::getline(initFile, dummy);
                continue;
            }
            /* stop on missing categoryName */
            if (!(initFile >> categoryName))
                break;

            log4shib::Category& category =
                (categoryName.compare("root") == 0) ?
                log4shib::Category::getRoot() :
                log4shib::Category::getInstance(categoryName);
            
            if (nextCommand.compare("appender") == 0) {
                std::string layout;
                std::string appenderName;
                
                if (initFile >> layout >> appenderName) {
                    log4shib::Appender* appender;
                    if (appenderName.compare("file") == 0) {
                        std::string logFileName;
                        if (!(initFile >> logFileName)) {
                            throw ConfigureFailure("Missing filename for log file logging configuration file for category: " + categoryName);
                        }
                        try {
                            appender = new log4shib::FileAppender(categoryName, logFileName);
                        }
                        catch (std::exception& ex) {
                            throw ConfigureFailure(std::string("Exception creating appender: ") + ex.what());
                        }
                    }
                    else if (appenderName.compare("rolling") == 0) {
                        std::string logFileName;
                        size_t maxFileSize;
                        unsigned int maxBackupIndex=1;
                        if (!(initFile >> logFileName)) {
                            throw ConfigureFailure("Missing filename for log file logging configuration file for category: " + categoryName);
                        }
                        if (!(initFile >> maxFileSize)) {
                            throw ConfigureFailure("Missing maximum size for log file logging configuration file for category: " + categoryName);
                        }
                        if (!(initFile >> maxBackupIndex)) {
                            throw ConfigureFailure("Missing maximum backup index for log file logging configuration file for category: " + categoryName);
                        }
                        try {
                            appender = new log4shib::RollingFileAppender(categoryName, logFileName, maxFileSize, maxBackupIndex);
                        }
                        catch (std::exception& ex) {
                            throw ConfigureFailure(std::string("Exception creating appender: ") + ex.what());
                        }
                    }
                    else if (appenderName.compare("console") == 0) {
                        try {
                            appender = new log4shib::OstreamAppender(categoryName, &std::cout);
                        }
                        catch (std::exception& ex) {
                            throw ConfigureFailure(std::string("Exception creating appender: ") + ex.what());
                        }
                    }
                    else if (appenderName.compare("stdout") == 0) {
                        try {
                            appender = new log4shib::FileAppender(categoryName, ::dup(fileno(stdout)));
                        }
                        catch (std::exception& ex) {
                            throw ConfigureFailure(std::string("Exception creating appender: ") + ex.what());
                        }
                    }
                    else if (appenderName.compare("stderr") == 0) {
                        try {
                            appender = new log4shib::FileAppender(categoryName, ::dup(fileno(stderr)));
                        }
                        catch (std::exception& ex) {
                            throw ConfigureFailure(std::string("Exception creating appender: ") + ex.what());
                        }
                    }
#if LOG4SHIB_HAVE_SYSLOG
                    else if (appenderName.compare("syslog") == 0) {
                        std::string syslogName;
                        int facility;
                        if (!(initFile >> syslogName)) {
                            throw ConfigureFailure("Missing syslogname for SysLogAppender for category: " + categoryName);
                        }
                        if (!(initFile >> facility)) {
                            facility = LOG_USER;
                        } else {
                            // * 8
                            facility *= 8;
                        }
                        try {
                            appender = new log4shib::SyslogAppender(categoryName, syslogName, facility);
                        }
                        catch (std::exception& ex) {
                            throw ConfigureFailure(std::string("Exception creating appender: ") + ex.what());
                        }
                    }
#endif
#if WIN32
                    else if (appenderName.compare("nteventlog") == 0) {
                        std::string source;
                        if (!(initFile >> source)) {
                            throw ConfigureFailure("Missing source for NTEventLogAppender for category: " + categoryName);
                        }
                        try {
                            appender = new log4shib::NTEventLogAppender(categoryName, source);
                        }
                        catch (std::exception& ex) {
                            throw ConfigureFailure(std::string("Exception creating appender: ") + ex.what());
                        }
                    }
#endif
                    else if (appenderName.compare("remotesyslog") == 0) {
                        std::string syslogName;
                        std::string relayer;
                        int facility;
                        int portNumber;
                        if (!(initFile >> syslogName)) {
                            throw ConfigureFailure("Missing syslogname for SysLogAppender for category: " + categoryName);
                        }
                        if (!(initFile >> relayer)) {
                            throw ConfigureFailure("Missing syslog host for SysLogAppender for category: " + categoryName);
                        }
                        if (!(initFile >> facility)) {
                            facility = LOG_USER;
                        }
                        if (!(initFile >> portNumber)) {
                            portNumber = 514;
                        }
                        try {
                            appender =
                                new log4shib::RemoteSyslogAppender(categoryName, syslogName, relayer, facility, portNumber);
                        }
                        catch (std::exception& ex) {
                            throw ConfigureFailure(std::string("Exception creating appender: ") + ex.what());
                        }
                    } 
                    else {
                        throw ConfigureFailure("Invalid appender name (" +
                                               appenderName +
                                               ") in logging configuration file for category: " +
                                               categoryName);
                    }
                    if (layout.compare("basic") == 0)
                        appender->setLayout(new log4shib::BasicLayout());
                    else if (layout.compare("simple") == 0)
                        appender->setLayout(new log4shib::SimpleLayout());
                    else if (layout.compare("pattern") == 0) {
                        log4shib::PatternLayout *layout = new log4shib::PatternLayout();
                        initFile >> std::ws; // skip whitespace
                        char pattern[1000];
                        initFile.getline(pattern, 1000);
                        layout->setConversionPattern(std::string(pattern));
                        appender->setLayout(layout);
                    }
                    else {
                        throw ConfigureFailure("Invalid layout (" + layout +
                                               ") in logging configuration file for category: " +
                                               categoryName);
                    }
                    category.addAppender(appender);
                }
            }
            else if (nextCommand.compare("priority") == 0) {
                std::string priority;
                if (!(initFile >> priority)) {
                    throw ConfigureFailure("Missing priority in logging configuration file for category: " + categoryName);
                }
                
                try {
                    category.setPriority(log4shib::Priority::getPriorityValue(priority));
                } catch(std::invalid_argument) {
                    throw ConfigureFailure("Invalid priority ("+priority+") in logging configuration file for category: "+categoryName);
                }
            }
            else if (nextCommand.compare("category") == 0) {
                /*
                  This command means we should "refer" to the category
                  (in order to have it created). We've already done this
                  in common setup code for all commands.
                */
            }
            else {
                throw ConfigureFailure("Invalid format in logging configuration file. Command: " + nextCommand);
            }
        }
    }
}



