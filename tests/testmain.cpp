#include <stdio.h>
#include "log4shib/Portability.hh"
#ifdef LOG4SHIB_HAVE_UNISTD_H
#include <unistd.h>
#endif
#include <iostream>
#include "log4shib/Category.hh"
#include "log4shib/Appender.hh"
#include "log4shib/FileAppender.hh"
#include "log4shib/OstreamAppender.hh"
#ifdef LOG4SHIB_HAVE_SYSLOG
#include "log4shib/SyslogAppender.hh"
#endif
#include "log4shib/Layout.hh"
#include "log4shib/BasicLayout.hh"
#include "log4shib/Priority.hh"
#include "log4shib/NDC.hh"

int main(int argc, char** argv) {
	log4shib::Appender* appender;
#ifdef LOG4SHIB_HAVE_SYSLOG
	log4shib::SyslogAppender* syslogAppender;

	syslogAppender = new log4shib::SyslogAppender("syslog", "log4shib");
#else
	log4shib::Appender* syslogAppender;

	syslogAppender = new log4shib::OstreamAppender("syslogdummy", &std::cout);
#endif

	if (argc < 2) {
		appender = new log4shib::OstreamAppender("default", &std::cout);
	} else {
		appender = new log4shib::FileAppender("default", argv[1]);
	}

	syslogAppender->setLayout(new log4shib::BasicLayout());
	appender->setLayout(new log4shib::BasicLayout());

	log4shib::Category& root = log4shib::Category::getRoot();
	root.addAppender(syslogAppender);
	root.setPriority(log4shib::Priority::ERROR);

	log4shib::Category& sub1 = log4shib::Category::getInstance(std::string("sub1"));
	sub1.addAppender(appender);

	log4shib::Category& sub2 = log4shib::Category::getInstance(std::string("sub1.sub2"));

	log4shib::NDC::push(std::string("ndc1"));

	std::cout << " root prio = " << root.getPriority() << std::endl;
	std::cout << " sub1 prio = " << sub1.getPriority() << std::endl;
	std::cout << " sub2 prio = " << sub2.getPriority() << std::endl;

	root.error("root error");
	root.warn("root warn");
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");
	sub2.error("sub2 error");
	sub2.warn("sub2 warn");

	sub1.setPriority(log4shib::Priority::INFO);
	std::cout << " root prio = " << root.getPriority() << std::endl;
	std::cout << " sub1 prio = " << sub1.getPriority() << std::endl;
	std::cout << " sub2 prio = " << sub2.getPriority() << std::endl;

	std::cout << "priority info" << std::endl;
	root.error("root error");
	root.warn("root warn");
	sub1.error("sub1 error");
	sub1.warn("sub1 warn");
	sub2.error("sub2 error");
	sub2.warn("sub2 warn");

	sub2.warnStream() << "streamed warn";

	sub2 << log4shib::Priority::WARN << "warn2" << " warn3" <<
		log4shib::eol << " warn4";

	{
		for(int i = 0; i < 10000; i++) {
			char ndc2[20];
			sprintf(ndc2, "i=%d", i);
			log4shib::NDC::push(ndc2);
			sub1.info("%s%d", "i = ", i);
			if ((i % 10) == 0) {
				sub1.log(log4shib::Priority::NOTICE, "reopen log");
				if (log4shib::Appender::reopenAll()) {
					sub1.info("log reopened");
				} else {
					sub1.warn("could not reopen log");
				}
			}
#ifndef WIN32
			sleep(1);
#endif
			log4shib::NDC::pop();
		}
	}

	return 0;
}
