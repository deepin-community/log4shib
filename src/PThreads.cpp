#include <log4shib/threading/Threading.hh>

#if defined(LOG4SHIB_HAVE_THREADING) && defined(LOG4SHIB_USE_PTHREADS)

#include <sstream>

namespace log4shib {
    namespace threading {

        std::string getThreadId() {
            std::ostringstream os;
            os << pthread_self();
            return os.str();
        }

    }
}

#endif // LOG4SHIB_HAVE_THREADING && LOG4SHIB_USE_PTHREADS
