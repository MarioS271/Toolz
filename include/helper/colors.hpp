/**
 * @file colors.hpp
 * @authors MarioS271
 */

#pragma once

#include <windows.h>

namespace Colors {
    namespace Fg {
        constexpr WORD black     = 0;
        constexpr WORD blue      = FOREGROUND_BLUE;
        constexpr WORD green     = FOREGROUND_GREEN;
        constexpr WORD red       = FOREGROUND_RED;
        constexpr WORD yellow    = FOREGROUND_RED | FOREGROUND_GREEN;
        constexpr WORD cyan      = FOREGROUND_GREEN | FOREGROUND_BLUE;
        constexpr WORD magenta   = FOREGROUND_RED | FOREGROUND_BLUE;
        constexpr WORD white     = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;

        constexpr WORD intense   = FOREGROUND_INTENSITY;
    }

    namespace Bg {
        constexpr WORD black     = 0;
        constexpr WORD blue      = BACKGROUND_BLUE;
        constexpr WORD green     = BACKGROUND_GREEN;
        constexpr WORD red       = BACKGROUND_RED;
        constexpr WORD yellow    = BACKGROUND_RED | BACKGROUND_GREEN;
        constexpr WORD cyan      = BACKGROUND_GREEN | BACKGROUND_BLUE;
        constexpr WORD magenta   = BACKGROUND_RED | BACKGROUND_BLUE;
        constexpr WORD white     = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

        constexpr WORD intense   = BACKGROUND_INTENSITY;
    }
}