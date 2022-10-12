/*
 * LayoutAppender.hh
 *
 * Copyright 2000, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2000, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4SHIB_LAYOUTAPPENDER_HH
#define _LOG4SHIB_LAYOUTAPPENDER_HH

#include <string>
#include <log4shib/Portability.hh>
#include <log4shib/AppenderSkeleton.hh>
#include <log4shib/BasicLayout.hh>

namespace log4shib {

    /**
     * LayoutAppender is a common superclass for all Appenders that require
     * a Layout. 
     **/
    class LOG4SHIB_EXPORT LayoutAppender : public AppenderSkeleton {
        public:

        typedef BasicLayout DefaultLayoutType;

        LayoutAppender(const std::string& name);
        virtual ~LayoutAppender();
        
        /**
         * Check if the appender requires a layout. All LayoutAppenders do,
         * therefore this method returns true for all subclasses.
         * 
         * @returns true.
         **/
        virtual bool requiresLayout() const;
        virtual void setLayout(Layout* layout = NULL);

        protected:
        /**
         * Return the layout of the appender.
         * This method is the Layout accessor for subclasses of LayoutAppender.
         * @returns the Layout.
         **/
        Layout& _getLayout();

        private:
        Layout* _layout;
    };
}

#endif // _LOG4SHIB_LAYOUTAPPENDER_HH

