#ifndef __RENDERER_H__
#define __RENDERER_H__

#ifdef OPENGL_BACKEND
    #include "backend/OpenGL/GLrender.h"
#else
    #error the engine currently only supports OpenGL backend!
#endif

#endif /* __RENDERER_H__ */
