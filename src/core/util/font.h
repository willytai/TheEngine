#ifndef __FONT_H__
#define __FONT_H__

#include "core/layer/layer.h"
#include <functional>
#include <vector>

namespace Engine7414
{
    struct fontStat
    {
        const char* filepath;
        float       size_pixels;
    };

    class FontLoader
    {
        friend class ImGuiLayer;
    public:
        // to make this work, make sure you load the font before the application starts (constructs)!!
        // this function actually stores the font instead of loading it directly
        // the font will load when any layer asks for it
        static void loadFromFile(const fontStat& stat);

    private:
        static void load(std::function<void(const char*, float)> loadFunc);

    private:
        static std::vector<fontStat> __fonts__;
    };
}

#endif /* __FONT_H__ */
