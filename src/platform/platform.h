#ifndef __PLATFORM_H__
#define __PLATFORM_H__

#include "config.h"

// Mac + OpenGL for now

#ifdef __APPLE__
    #include "Mac/macWindow.h"
#elif _WIN64
    #include "Windows/windowsWindow.h"
#else
    #error Engine7414 currently supports Mac and 64-bit Windows only!
#endif

#endif /* __PLATFORM_H__ */
