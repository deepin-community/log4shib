#include <cstdlib>
#include <cstring>
#include <cstdio>
#include <iostream>

#include <log4shib/Category.hh>
#include <log4shib/OstreamAppender.hh>
#include <log4shib/FileAppender.hh>
#include <log4shib/BasicLayout.hh>
#include <log4shib/PatternLayout.hh>
#include <log4shib/TimeStamp.hh>

#include "Clock.hh"


// -----------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    int    count  = argc > 1 ? std::atoi(argv[1]) : 100;
    size_t size   = argc > 2 ? std::atoi(argv[2]) : 128;    

    std::cout << "  count: " << count << std::endl
	      << "   size: " << size  << " bytes" << std::endl
	      << std::endl;

    log4shib::Category&	root	 = log4shib::Category::getRoot();
    root.setPriority(log4shib::Priority::ERROR);    

    log4shib::OstreamAppender ostreamAppender("cerr", &std::cerr);
    log4shib::FileAppender fileAppender("stderr", fileno(stderr));
    ostreamAppender.setLayout(new log4shib::BasicLayout());
    fileAppender.setLayout(new log4shib::BasicLayout());

    root.removeAllAppenders();
    root.addAppender(ostreamAppender);

    log4shib::Category& log = log4shib::Category::getInstance("someCategory");

    Clock  clock;
    char*  buffer = new char[size + 1];
    
    std::memset(buffer, 'X', size + 1);
    buffer[size] = '\0';

    std::cout << "BasicLayout:" << std::endl;
    {	
	clock.start();
	for (int i = 0; i < count; i++) log.error("%s", buffer);    
	clock.stop();
	std::cout << "  charbuf printf  ostream:  " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }
    
    {	
        const char* buffer2 = buffer;
	clock.start();
	for (int i = 0; i < count; i++) log.error(std::string(buffer2));    
	clock.stop();
	std::cout << "  charbuf string  ostream:  " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }

    {
	std::string str(size, 'X');

	clock.start();
	for (int i = 0; i < count; i++) 
            log << log4shib::Priority::ERROR << str;
	clock.stop();
	std::cout << "  string  stream  ostream:  " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }

    {
	clock.start();
	for (int i = 0; i < count; i++) 
            log << log4shib::Priority::ERROR << buffer;
	clock.stop();
	std::cout << "  charbuf stream  ostream:  " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }
    
    {
	std::string str(size, 'X');

	clock.start();
        log4shib::CategoryStream s(log << log4shib::Priority::ERROR);
	for (int i = 0; i < count; i++) 
            s << str << log4shib::eol;
	clock.stop();
	std::cout << "  string  stream2 ostream:  " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }

    {
	clock.start();
        log4shib::CategoryStream s(log << log4shib::Priority::ERROR);
	for (int i = 0; i < count; i++) 
            s << buffer << log4shib::eol;
	clock.stop();
	std::cout << "  charbuf stream2 ostream:  " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }
    
    {
	std::string str(size, 'X');
	
	clock.start();
	for (int i = 0; i < count; i++) log.error(str);
	clock.stop();
	std::cout << "  direct  string  ostream:  " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }

    {
	std::string str(size, 'X');
        root.removeAllAppenders();
        root.addAppender(fileAppender);

	clock.start();
	for (int i = 0; i < count; i++) log.error(str);
	clock.stop();
	std::cout << "  direct  string  file:     " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }

    std::cout << "PatternLayout:" << std::endl;
    {
        log4shib::PatternLayout* patternLayout = new log4shib::PatternLayout();
        patternLayout->setConversionPattern("%R %p %c %x: %m\n");
        ostreamAppender.setLayout(patternLayout);
    }
    {
        log4shib::PatternLayout* patternLayout = new log4shib::PatternLayout();
        patternLayout->setConversionPattern("%R %p %c %x: %m\n");
        fileAppender.setLayout(patternLayout);
    }

    root.removeAllAppenders();
    root.addAppender(ostreamAppender);

    {	
	clock.start();
	for (int i = 0; i < count; i++) log.error("%s", buffer);    
	clock.stop();
	std::cout << "  charbuf printf ostream:  " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }
    
    {
	std::string str(size, 'X');
	
	clock.start();
	for (int i = 0; i < count; i++) log.error(str);
	clock.stop();
	std::cout << "  direct  string ostream:  " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }

    {
	std::string str(size, 'X');
        root.removeAllAppenders();
        root.addAppender(fileAppender);

	clock.start();
	for (int i = 0; i < count; i++) log.error(str);
	clock.stop();
	std::cout << "  string  file:     " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }

    {
	clock.start();
	for (int i = 0; i < count; i++) fprintf(stderr, "%d ERROR someCategory : %s\n", log4shib::TimeStamp().getSeconds(), buffer);
	clock.stop();
	std::cout << std::endl << "  fprintf:        " << ((float)clock.elapsed()) / count << " us" << std::endl;
    }

    delete[] buffer;
    log4shib::Category::shutdown();

    return 0;
}
