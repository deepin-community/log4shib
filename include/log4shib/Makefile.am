SUBDIRS = threading

liblog4shibincludedir = $(includedir)/log4shib
liblog4shibinclude_HEADERS =  \
	Appender.hh \
	AppenderSkeleton.hh \
	FixedContextCategory.hh \
	LayoutAppender.hh \
	FileAppender.hh \
	RollingFileAppender.hh \
	IdsaAppender.hh \
	OstreamAppender.hh \
	StringQueueAppender.hh \
	SyslogAppender.hh \
	RemoteSyslogAppender.hh \
	Layout.hh \
	SimpleLayout.hh \
	BasicLayout.hh \
	PatternLayout.hh \
	Category.hh \
	CategoryStream.hh \
	HierarchyMaintainer.hh \
	Configurator.hh \
	BasicConfigurator.hh \
	SimpleConfigurator.hh \
	PropertyConfigurator.hh \
	LoggingEvent.hh \
	Priority.hh \
	NDC.hh \
	TimeStamp.hh \
	Filter.hh \
	Export.hh \
	Portability.hh \
	Win32DebugAppender.hh \
	NTEventLogAppender.hh \
	AbortAppender.hh \
	config.h \
	config-win32.h \
	config-openvms.h

dist-hook:
	rm -f $(distdir)/config.h

distclean-local:
	rm -f config.h
