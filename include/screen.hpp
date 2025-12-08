/**
 * @file screen.hpp
 * @authors MarioS271
 */

#include "anchors.hpp"

namespace screen {
    inline SHORT width() {
        return anchor::bottomRight().X;
    }

    inline SHORT height() {
        return anchor::bottomRight().Y;
    }
}