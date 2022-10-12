/*
 * PatternLayout.hh
 *
 * Copyright 2002, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4SHIB_PATTERNLAYOUT_HH
#define _LOG4SHIB_PATTERNLAYOUT_HH

#include <log4shib/Portability.hh>
#include <log4shib/Layout.hh>
#include <log4shib/Configurator.hh>
#include <vector>
#ifdef LOG4SHIB_HAVE_SSTREAM
#include <sstream>
#endif

namespace log4shib {

    /**
     * PatternLayout is a simple fixed format Layout implementation. 
     **/
    class LOG4SHIB_EXPORT PatternLayout : public Layout {
        public:
        /**
           The default conversion pattern
        **/
        static const char* DEFAULT_CONVERSION_PATTERN;

        /**
           A conversion pattern equivalent to the SimpleLayout.
        **/
        static const char* SIMPLE_CONVERSION_PATTERN;

        /**
           A conversion pattern equivalent to the BasicLayout.
        **/
        static const char* BASIC_CONVERSION_PATTERN;

        /**
           A conversion pattern equivalent to the TTCCLayout.
           Note: TTCCLayout is in log4j but not log4shib.
        **/           
        static const char* TTCC_CONVERSION_PATTERN;

        PatternLayout();
        virtual ~PatternLayout();
        
        /**
           Formats the LoggingEvent in the style set by
           the setConversionPattern call. By default, set
           to "%m%n"
         **/
        virtual std::string format(const LoggingEvent& event);

        /**
           Sets the format of log lines handled by this
           PatternLayout. By default, set to "%m%n".
           Format characters are as follows:
           - <b>%%</b> - a single percent sign
           - <b>%%c</b> - the category
           - <b>%%d</b> - the date\n
            Date format: The date format character may be followed by a date format
            specifier enclosed between braces. For example, %%d{%%H:%%M:%%S,%%l} or %%d{%%d %%m %%Y %%H:%%M:%%S,%%l}.
            If no date format specifier is given then the following format is used:
            "Wed Jan 02 02:03:55 1980". The date format specifier admits the same syntax
            as the ANSI C function strftime, with 1 addition. The addition is the specifier
            %%l for milliseconds, padded with zeros to make 3 digits.
           - <b>%%m</b> - the message
           - <b>%%n</b> - the platform specific line separator
           - <b>%%p</b> - the priority
           - <b>%%r</b> - milliseconds since this layout was created
           - <b>%%R</b> - seconds since Jan 1, 1970
           - <b>%%u</b> - clock ticks since process start
           - <b>%%x</b> - the NDC
 
           @param conversionPattern the conversion pattern
           @exception ConfigureFailure if the pattern is invalid
         **/
        virtual void setConversionPattern(const std::string& conversionPattern);

        virtual std::string getConversionPattern() const;

        virtual void clearConversionPattern();

        class LOG4SHIB_EXPORT PatternComponent {
            public:
            inline virtual ~PatternComponent() {};
            virtual void append(std::ostringstream& out, const LoggingEvent& event) = 0;
        };

        private:
        typedef std::vector<PatternComponent*> ComponentVector; 
        ComponentVector _components;

        std::string _conversionPattern;
    };        
}

#endif // _LOG4SHIB_PATTERNLAYOUT_HH
