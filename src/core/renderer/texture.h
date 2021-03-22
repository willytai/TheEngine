#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "core/core.h"

namespace Engine7414
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual void bind(uint32_t slot = 0) const = 0;
        virtual void unbind() const = 0;

        virtual int width() const = 0;
        virtual int height() const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        virtual ~Texture2D() = default;

        virtual void bind(uint32_t slot = 0) const override = 0;
        virtual void unbind() const override = 0;

        virtual int width() const override = 0;
        virtual int height() const override = 0;

        static Ref<Texture2D> create(const char* filepath);
    };
}

#endif
