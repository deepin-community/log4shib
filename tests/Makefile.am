TESTS = testCategory testFixedContextCategory testNDC testPattern \
	testErrorCollision testPriority testFilter testProperties \
	testConfig testPropertyConfig sscpp706

check_PROGRAMS = $(TESTS) testmain testbench
check_DATA = log4shib.init log4shib.properties testProperties.properties \
	testConfig.log4shib.properties sscpp706.txt

EXTRA_DIST = $(check_DATA) testNTEventLog.cpp

AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/src
LDADD = ../src/liblog4shib.la $(PTHREAD_LIBS)
AM_DEFAULT_SOURCE_EXT = .cpp

sscpp706_CPPFLAGS = $(AM_CPPFLAGS) -DDATADIR=\"$(srcdir)\"

testbench_SOURCES = Clock.cpp Clock.hh testbench.cpp 

distclean-local:
	$(RM) -f *.log
