// testConfig.cpp : Derived from testPattern.cpp.
//

#include <log4shib/Portability.hh>

#ifdef WIN32
#include <windows.h>
#endif
#ifdef LOG4SHIB_HAVE_UNISTD_H
#include <unistd.h>
#endif

#include <cstdlib>

#include <log4shib/Category.hh>
#include <log4shib/Appender.hh>
#include <log4shib/OstreamAppender.hh>
#include <log4shib/FileAppender.hh>
#include <log4shib/Layout.hh>
#include <log4shib/BasicLayout.hh>
#include <log4shib/Priority.hh>
#include <log4shib/NDC.hh>
#include <log4shib/PatternLayout.hh>

#include <log4shib/SimpleConfigurator.hh>

double calcPi()
{
    double denominator = 3.0;
    double retVal = 4.0;
    long i;
    for (i = 0; i < 50000000l; i++)
    {
        retVal = retVal - (4.0 / denominator);
        denominator += 2.0;
        retVal = retVal + (4.0 /denominator);
        denominator += 2.0;
    }
    return retVal;
}

int main(int argc, char* argv[])
{
    try {
        /* looking for the init file in $srcdir is a requirement of
           automake's distcheck target.
        */
        char* srcdir = std::getenv("srcdir");
        std::string initFileName;
        if (srcdir == NULL) {
            initFileName = "./log4shib.init";
        }
        else {
            initFileName = std::string(srcdir) + "/log4shib.init";
        }
        log4shib::SimpleConfigurator::configure(initFileName);
    } catch(log4shib::ConfigureFailure& f) {
        std::cout << "Configure Problem " << f.what() << std::endl;
        return -1;
    }

    log4shib::Category& root = log4shib::Category::getRoot();

    log4shib::Category& sub1 = 
        log4shib::Category::getInstance(std::string("sub1"));

    log4shib::Category& sub2 = 
        log4shib::Category::getInstance(std::string("sub1.sub2"));

    root.error("root error");
    root.warn("root warn");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");

    calcPi();

    sub2.error("sub2 error");
    sub2.warn("sub2 warn");

    root.error("root error");
    root.warn("root warn");
    sub1.error("sub1 error");
    sub1.warn("sub1 warn");

#ifdef WIN32
    Sleep(3000);
#else
    sleep(3);
#endif

    sub2.error("sub2 error");
    sub2.warn("sub2 warn");
    sub2.error("%s %s %d", "test", "vform", 123);
    sub2.warnStream() << "streamed warn";

    sub2 << log4shib::Priority::WARN << "warn2.." << "..warn3..value=" << 0 << 
        log4shib::eol << "..warn4";

    log4shib::Category::shutdown();

    return 0;
}

