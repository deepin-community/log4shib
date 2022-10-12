/*
 * CategoryStream.hh
 *
 * Copyright 2001, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2001, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4SHIB_CATEGORYSTREAM_HH
#define _LOG4SHIB_CATEGORYSTREAM_HH

#include <log4shib/Portability.hh>
#include <log4shib/Priority.hh>
#ifdef LOG4SHIB_HAVE_SSTREAM
#include <sstream>
#endif

namespace log4shib {

    class LOG4SHIB_EXPORT Category;
    class LOG4SHIB_EXPORT CategoryStream;

    /**
     * eol manipulator
     **/
    LOG4SHIB_EXPORT CategoryStream& eol (CategoryStream& os);

    /**
     * This class enables streaming simple types and objects to a category.
     * Use category.errorStream(), etc. to obtain a CategoryStream class.
     **/
    class LOG4SHIB_EXPORT CategoryStream {
        public:

        /**
         * Construct a CategoryStream for given Category with given priority.
         * @param category The category this stream will send log messages to.
         * @param priority The priority the log messages will get or 
         * Priority::NOTSET to silently discard any streamed in messages.
         **/
        CategoryStream(Category& category, Priority::Value priority);

        /**
         * Destructor for CategoryStream
         **/
        ~CategoryStream();
        
        /**
         * Returns the destination Category for this stream.
         * @returns The Category.
         **/
        inline Category& getCategory() const { return _category; };

        /**
         * Returns the priority for this stream.
         * @returns The priority.
         **/
        inline Priority::Value getPriority() const throw() { 
            return _priority; 
        };

        /**
         * Flush the contents of the stream buffer to the Category and
         * empties the buffer.
         **/
        void flush();

        /**
         * Stream in arbitrary types and objects.  
         * @param t The value or object to stream in.
         * @returns A reference to itself.
         **/
        template<typename T> CategoryStream& operator<<(const T& t) {
            if (getPriority() != Priority::NOTSET) {
                if (!_buffer) {
                    if (!(_buffer = new std::ostringstream)) {
                        // XXX help help help
                    }
                }
                (*_buffer) << t;
            }
            return *this;
        }
        
        private:
        Category& _category;
        Priority::Value _priority;
        std::ostringstream* _buffer;

     public:
        typedef CategoryStream& (*cspf) (CategoryStream&);
        CategoryStream& operator << (cspf);
        LOG4SHIB_EXPORT friend CategoryStream& eol (CategoryStream& os);
    };

}
#endif // _LOG4SHIB_CATEGORYSTREAM_HH
