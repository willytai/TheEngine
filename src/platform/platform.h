#ifndef __PLATFORM_H__
#define __PLATFORM_H__

// Mac + OpenGL for now

#ifndef ENGINE_BACKEND_OPENGL
    #error Engine7414 only supports OpenGL backend currently!
#endif

#ifdef __APPLE__
    #include "macWindow.h"
#else
    #error Engine7414 currently supports Mac only!
#endif

#endif /* __PLATFORM_H__ */
