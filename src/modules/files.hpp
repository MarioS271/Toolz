/**
 * @file files.hpp
 * @authors MarioS271
 */

#pragma once

#include <windows.h>
#include "class/panel.hpp"
#include "helper/anchors.hpp"
#include "helper/colors.hpp"
#include "helper/clearMain.hpp"
#include "constants.hpp"

class FilesPanel : public Panel {
public:
    void redraw(Renderer &r) override {
        clearMain(r);

        COORD pos = anchor::center();
        pos.X -= 6;

        r.drawText(pos, L"Files Content", Colors::Fg::red | Colors::Fg::intense);
    }
};