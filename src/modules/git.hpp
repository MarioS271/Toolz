/**
 * @file git.hpp
 * @authors MarioS271
 */

#pragma once

#include <windows.h>
#include "class/panel.hpp"
#include "helper/anchors.hpp"
#include "helper/colors.hpp"
#include "helper/clear_main.hpp"
#include "helper/short_cast.hpp"
#include "constants.hpp"

class GitPanel : public Panel {
public:
    void redraw(Renderer &r) override {
        clearMain(r);

        COORD pos = anchor::center();
        pos.X -= 5;

        r.drawText(pos, L"Git Content", Colors::Fg::red | Colors::Fg::intense);
    }
};