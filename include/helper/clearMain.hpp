/**
 * @file clearMain.hpp
 * @authors MarioS271
 */

#pragma once

#include <windows.h>
#include "class/renderer.hpp"
#include "helper/anchors.hpp"

void clearMain(Renderer& r) {
    COORD size = {
        anchor::right(),
        static_cast<SHORT>(anchor::right() - 2),
    };
    COORD anchor_lu = {
        anchor::topLeft().X,
        static_cast<SHORT>(anchor::topLeft().Y + 1),
    };
    r.clearArea(anchor_lu, size);
}