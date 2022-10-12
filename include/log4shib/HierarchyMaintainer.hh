/*
 * HierarchyMaintainer.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4SHIB_HIERARCHYMAINTAINER_HH
#define _LOG4SHIB_HIERARCHYMAINTAINER_HH

#include <log4shib/Portability.hh>
#include <string>
#include <map>
#include <vector>
#include <log4shib/Category.hh>
#include <log4shib/threading/Threading.hh>

namespace log4shib {

    /**
     * HierarchyMaintainer is an internal log4shib class. It is responsible
     * for maintaining the hierarchy of Categories. Applications should
     * not have to use this class directly.
     **/
    class HierarchyMaintainer {
        friend class Log4cppCleanup;

        public:
        typedef std::map<std::string, Category*> CategoryMap;
  
        static HierarchyMaintainer& getDefaultMaintainer();

        HierarchyMaintainer();
        virtual ~HierarchyMaintainer();
        virtual Category* getExistingInstance(const std::string& name);
        virtual Category& getInstance(const std::string& name);
        virtual std::vector<Category*>* getCurrentCategories() const;
        virtual void shutdown();
        virtual void deleteAllCategories();

        protected:
        virtual Category* _getExistingInstance(const std::string& name);
        virtual Category& _getInstance(const std::string& name);
        CategoryMap _categoryMap;
        mutable threading::Mutex _categoryMutex;

        private:
        static HierarchyMaintainer* _defaultMaintainer;
    };        
}

#endif // _LOG4SHIB_HIERARCHYMAINTAINER_HH
