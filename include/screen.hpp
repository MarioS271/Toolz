/**
 * @file screen.hpp
 * @authors MarioS271
 */

#pragma once

#include "anchors.hpp"

namespace screen {
    inline SHORT width() {
        return anchor::bottomRight().X + (SHORT)1;
    }

    inline SHORT height() {
        return anchor::bottomRight().Y + (SHORT)1;
    }
}