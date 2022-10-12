#include <stdio.h>
#include <iostream>
#include "log4shib/FixedContextCategory.hh"
#include "log4shib/Appender.hh"
#include "log4shib/OstreamAppender.hh"
#include "log4shib/Layout.hh"
#include "log4shib/BasicLayout.hh"
#include "log4shib/Priority.hh"
#include "log4shib/NDC.hh"

int main(int argc, char** argv) {    
    log4shib::Appender* appender = 
        new log4shib::OstreamAppender("default", &std::cout);

    log4shib::Layout* layout = new log4shib::BasicLayout();
    appender->setLayout(layout);

    log4shib::Category& root = log4shib::Category::getRoot();
    root.addAppender(appender);
       root.setPriority(log4shib::Priority::ERROR);
    
    log4shib::FixedContextCategory sub1(std::string("sub1"), std::string("context1"));

    log4shib::FixedContextCategory sub1_2(std::string("sub1"), std::string("context1_2"));

    log4shib::FixedContextCategory sub2(std::string("sub1.sub2"), std::string("context2"));

    std::cout << " root priority = " << root.getPriority() << std::endl;
    std::cout << " sub1 priority = " << sub1.getPriority() << std::endl;
    std::cout << " sub2 priority = " << sub2.getPriority() << std::endl;
    
    root.error("root error");
    root.warn("root warn");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");
    sub1_2.error("sub1 error");
    sub1_2.warn("sub1 warn");
    sub2.error("sub2 error");
    sub2.warn("sub2 warn");
    
    log4shib::Category::getInstance(std::string("sub1")).
               setPriority(log4shib::Priority::INFO);

    std::cout << " root priority = " << root.getPriority() << std::endl;
    std::cout << " sub1 priority = " << sub1.getPriority() << std::endl;
    std::cout << " sub2 priority = " << sub2.getPriority() << std::endl;
   
    std::cout << "priority info" << std::endl;
    root.error("root error");
    root.warn("root warn");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");
    sub2.error("sub2 error");
    sub2.warn("sub2 warn");
    sub2.error("%s %s %d", "test", "vform", 123);
    sub2.warnStream() << "streamed warn";

    sub2 << log4shib::Priority::WARN << "warn2.." << "..warn3..value=" << 0 << 
        log4shib::eol << "..warn4";

    log4shib::Category::shutdown();

    return 0;
}
