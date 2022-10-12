/*
 * PropertyConfigurator.cpp
 *
 * Copyright 2001, Glen Scott. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */
#include "PortabilityImpl.hh"
#include <log4shib/PropertyConfigurator.hh>
#include "PropertyConfiguratorImpl.hh"

namespace log4shib {

    void PropertyConfigurator::configure(const std::string& initFileName) {
        PropertyConfiguratorImpl configurator;
        
        configurator.doConfigure(initFileName);
    }
}

