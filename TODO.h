#ifndef TODO_H_
#define TODO_H_

#ifdef WIN32

#pragma once

#define STRING2(x) #x
#define STRING(x) STRING2(x)

#define TODO(x) message(__FILE__ "(" STRING(__LINE__) ") : TODO: " x)
#define todo(x) TODO(x)

#else //g++ on linux

#define DO_PRAGMA(x) _Pragma(#x)
#define MESSAGE_PRAGMA(x, y) DO_PRAGMA( message ( x " - " y ) )
#define TODO(x) MESSAGE_PRAGMA("TODO", x)

#endif

#endif
