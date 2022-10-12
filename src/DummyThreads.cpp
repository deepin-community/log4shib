#include <log4shib/threading/Threading.hh>

#ifndef LOG4SHIB_HAVE_THREADING

namespace log4shib {
    namespace threading {

        std::string getThreadId() {
            // more useful would be to return the PID.
            return std::string("thread1");
        }

    }
}

#endif // LOG4SHIB_HAVE_THREADING
