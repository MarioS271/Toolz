/**
 * @file anchors.hpp
 * @authors MarioS271
 */

#pragma once

#include <windows.h>

namespace anchor {
    inline CONSOLE_SCREEN_BUFFER_INFO csbi() {
        CONSOLE_SCREEN_BUFFER_INFO _csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &_csbi);
        return _csbi;
    }

    inline SHORT top() {
        return SHORT{0};
    }
    inline SHORT bottom() {
        return static_cast<SHORT>(csbi().dwSize.Y - 1);
    }
    inline SHORT left() {
        return SHORT{0};
    }
    inline SHORT right() {
        return static_cast<SHORT>(csbi().dwSize.X);
    }

    inline COORD topLeft() {
        return {
            left(),
            top(),
        };
    }
    inline COORD topRight() {
        return {
            right(),
            top(),
        };
    }
    inline COORD bottomLeft() {
        return {
            left(),
            bottom(),
        };
    }
    inline COORD bottomRight() {
        return {
            right(),
            bottom(),
        };
    }

    inline COORD topLeftVA() {
        return {
            left(),
            static_cast<SHORT>(top() + 1),
        };
    }
    inline COORD topRightVA() {
        return {
            right(),
            static_cast<SHORT>(top() + 1),
        };
    }
    inline COORD bottomLeftVA() {
        return {
            left(),
            static_cast<SHORT>(bottom() - 1),
        };
    }
    inline COORD bottomRightVA() {
        return {
            right(),
            static_cast<SHORT>(bottom() - 1),
        };
    }

    inline COORD center() {
        return {
            static_cast<SHORT>(right() / 2),
            static_cast<SHORT>(bottom() / 2),
        };
    }
}