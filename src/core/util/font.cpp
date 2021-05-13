#include "core/util/font.h"
#include <iostream>

namespace Engine7414
{
    std::vector<std::pair<fontStat, FontLoader::Type> > FontLoader::__fonts__;

    void  FontLoader::loadFromFile(const fontStat& stat, const Type& type) {
        __fonts__.emplace_back( stat, type );
    }

    void FontLoader::load(std::function<void(const char*, float, Type)> loadFunc) {
        for (const auto& [fontStat, type] : __fonts__) {
            loadFunc( fontStat.filepath, fontStat.size_pixels, type );
        }
    }
}
