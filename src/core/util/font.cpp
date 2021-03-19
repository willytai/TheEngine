#include "core/util/font.h"
#include <iostream>

namespace Engine7414
{
    std::vector<fontStat> FontLoader::__fonts__;

    void  FontLoader::loadFromeFile(const fontStat& stat) {
        __fonts__.emplace_back( stat );
    }

    void FontLoader::load(std::function<void(const char*, float)> loadFunc) {
        for (const auto& font : __fonts__) {
            loadFunc( font.filepath, font.size_pixels );
        }
    }
}
