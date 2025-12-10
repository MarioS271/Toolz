/**
 * @file constants.hpp
 * @authors MarioS271
 */

#pragma once

#include <string>
#include <windows.h>

namespace constants {
    constexpr std::wstring_view VERSION = L"1.0";
    constexpr SHORT FRAMERATE = 30;
    constexpr bool MOUSE_CLICK_INFO = true;
}