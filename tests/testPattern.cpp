// testLog4CPP.cpp : Derived from testCategory.cpp
//
#include <log4shib/Category.hh>
#include <log4shib/Appender.hh>
#include <log4shib/Priority.hh>
#include <log4shib/NDC.hh>
#include <log4shib/PatternLayout.hh>
#include <log4shib/BasicConfigurator.hh>
#include <iostream>

void test(std::string pattern, log4shib::PatternLayout* layout, log4shib::Category& cat)
{
    try {	
        layout->setConversionPattern(pattern);
        cat.error("message");
    } catch(log4shib::ConfigureFailure& f) {
        std::cerr << "configure failure: " << f.what() << std::endl;
    }	
}                                                                              

int main(int argc, char* argv[])
{
    log4shib::BasicConfigurator::configure();
    log4shib::PatternLayout* layout = new log4shib::PatternLayout();
    log4shib::Category::getRoot().getAppender()->setLayout(layout);

    log4shib::Category& cat = log4shib::Category::getInstance("cat1");
    
    log4shib::NDC::push("ndc1");

    test("%% %r %c:%d (%R / %r) [%p] %x %m %% (%u) %n", layout, cat);

    // test format specifiers
    test(">%10m<%n", layout, cat);
    test(">%-10m<%n", layout, cat);
    test(">%3.5m<%n", layout, cat);
    test(">%.5m<%n", layout, cat);

    // category test
    test(">%c{2}<%n", layout, log4shib::Category::getInstance("c1.c2.c3.c4"));

    // test date format
    test("%d{%d %b %Y %H:%M:%S.%l} %m %n", layout, cat);
    test("%d{%d %b %Y %H:%M:%S.%l", layout, cat);
    test("%d%n", layout, cat);

    test("%m %d%n", layout, cat);
    int i;
    for (i = 0; i < 10; i++) {
        cat.error("%d message", i);
    }
    test("%m %d{%H:%M:%S.%l %d %b %Y}%n", layout, cat);
    for (i = 0; i < 10; i++) {
        cat.error("%d message", i);
    }

    // test bug #688715
    test("%.10m", layout, cat);

    log4shib::Category::shutdown();

    return 0;
}

