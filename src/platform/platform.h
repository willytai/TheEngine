#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "config.h"

// Mac + OpenGL for now

#ifdef __APPLE__
    #include "macWindow.h"
#else
    #error Engine7414 currently supports Mac only!
#endif

#endif /* __PLATFORM_H__ */
