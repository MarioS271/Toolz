/**
 * @file clearMain.hpp
 * @authors MarioS271
 */

#pragma once

#include <windows.h>
#include "class/renderer.hpp"
#include "helper/anchors.hpp"
#include "helper/short_cast.hpp"

void clearMain(Renderer& r) {
    COORD size = {
        anchor::right(),
        scast(anchor::bottom() - 2),
    };
    r.clearArea(anchor::topLeftVA(), size);
}