/**
 * @file anchors.hpp
 * @authors MarioS271
 */

#pragma once

#include <windows.h>

namespace anchor {
    inline COORD topLeft()
    {
        return {
            static_cast<SHORT>(0),
            static_cast<SHORT>(0)
        };
    }

    inline COORD topRight()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return {
            static_cast<SHORT>(csbi.dwSize.X - 1),
            static_cast<SHORT>(0)
        };
    }

    inline COORD bottomLeft()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return {
            static_cast<SHORT>(0),
            static_cast<SHORT>(csbi.dwSize.Y - 1)
        };
    }

    inline COORD bottomRight()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return {
            static_cast<SHORT>(csbi.dwSize.X - 1),
            static_cast<SHORT>(csbi.dwSize.Y - 1)
        };
    }

    inline COORD center()
    {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
        return {
            static_cast<SHORT>(csbi.dwSize.X / 2),
            static_cast<SHORT>(csbi.dwSize.Y / 2)
        };
    }
}