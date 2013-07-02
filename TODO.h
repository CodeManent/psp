#ifndef TODO_H_
#define TODO_H_

#pragma once

#define STRING2(x) #x
#define STRING(x) STRING2(x)

#define TODO(x) message(__FILE__ "(" STRING(__LINE__) ") : TODO: " x)
#define todo(x) TODO(x)

#endif
