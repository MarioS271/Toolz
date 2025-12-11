/**
 * @file short_cast.hpp
 * @authors MarioS271
*/

#pragma once

#include <windows.h>

/**
 * @brief Wrapper for static_cast<SHORT>(value)
 *
 * @return SHORT
 *
 * @param value The value to cast
 */
inline SHORT scast(auto value) {
    return static_cast<SHORT>(value);
}