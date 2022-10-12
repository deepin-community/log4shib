/*
 * SimpleConfigurator.hh
 *
 * Copyright 2001, Glen Scott. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */
#ifndef _LOG4SHIB_SIMPLECONFIGURATOR_HH
#define _LOG4SHIB_SIMPLECONFIGURATOR_HH

#include <log4shib/Portability.hh>
#include <iostream>
#include <string>
#include <log4shib/Configurator.hh>

namespace log4shib {

    /**
     * This class implements a simple Configurator for log4shib.
     * It is a temporary hack with an undocumented configuration format.
     * @deprecated As of version 0.3.2 log4shib includes a log4j format 
     * compatible PropertyConfigurator, removing the need for 
     * SimpleConfigurator. This class will be removed in 0.4.0.
     **/
    class LOG4SHIB_EXPORT SimpleConfigurator {
    public:

        /**
         * Configure log4shib with the configuration in the given file.
         * NB. The configuration file format is undocumented and may change
         * without notice.
         * @since 0.2.6
         * @param initFileName name of the configuration file
         * @exception ConfigureFailure if the method encountered a read or 
         * syntax error.
         **/
        static void configure(const std::string& initFileName);

        /**
         * Configure log4shib with the configuration in the given file.
         * NB. The configuration file format is undocumented and may change
         * without notice.
         * @since 0.3.1
         * @param initFile an input stream to the configuration file
         * @exception ConfigureFailure if the method encountered a read or 
         * syntax error.
         **/
        static void configure(std::istream& initFile);
    };
}

#endif
