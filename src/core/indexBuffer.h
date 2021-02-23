#ifndef __INDEX_BUFFER_H__
#define __INDEX_BUFFER_H__

#include "GLmacro.h"

class IndexBufferUI
{
public:
    IndexBufferUI(const GLuint* data, unsigned int count);
    ~IndexBufferUI();

    void bind() const;
    void unbind() const;

    inline int count() const { return (int)_count; }

private:
    GLuint       _rendererID;
    unsigned int _count;
};

#endif /* __INDEX_BUFFER_H__ */
