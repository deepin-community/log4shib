/*
 * Threading.hh
 *
 * Copyright 2002, LifeLine Networks BV (www.lifeline.nl). All rights reserved.
 * Copyright 2002, Bastiaan Bakker. All rights reserved.
 *
 * See the COPYING file for the terms of usage and distribution.
 */

#ifndef _LOG4SHIB_THREADING_THREADING_HH
#define _LOG4SHIB_THREADING_THREADING_HH

#include <log4shib/Portability.hh>

#ifdef LOG4SHIB_HAVE_THREADING

#ifdef LOG4SHIB_USE_OMNITHREADS
#include <log4shib/threading/OmniThreads.hh>
#endif

#ifdef LOG4SHIB_USE_BOOSTTHREADS
#include <log4shib/threading/BoostThreads.hh>
#endif

#ifdef LOG4SHIB_USE_MSTHREADS
#include <log4shib/threading/MSThreads.hh>
#endif

#ifdef LOG4SHIB_USE_PTHREADS
#include <log4shib/threading/PThreads.hh>
#endif

#else /* LOG4SHIB_HAVE_THREADING */
#include <log4shib/threading/DummyThreads.hh>
#endif /* LOG4SHIB_HAVE_THREADING */

#endif
