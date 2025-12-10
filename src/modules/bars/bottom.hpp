/**
 * @file bottom.hpp
 * @authors MarioS271
 */

#pragma once

#include <windows.h>
#include "class/panel.hpp"
#include "helper/anchors.hpp"
#include "helper/colors.hpp"
#include "constants.hpp"

class BottomBar : public Panel {
public:
    void redraw(Renderer &r) override {
        WORD color = Colors::Fg::white | Colors::Fg::intense | Colors::Bg::blue | Colors::Bg::intense;

        COORD size = {
            anchor::right(),
            SHORT{1},
        };
        r.drawRegion(anchor::bottomLeft(), size, color);

        COORD drawPos = anchor::bottomLeft();
        std::wstring text{L""};

        // Version
        text = L"Toolz v" + std::wstring(constants::VERSION);
        r.drawText(drawPos, text, color);
        drawPos.X += static_cast<SHORT>(text.length() + 2);

        // Viewport Resolution
        text = std::to_wstring(anchor::right()) + L"x" + std::to_wstring(anchor::right());
        r.drawText(drawPos, text, color);
        drawPos.X += static_cast<SHORT>(text.length() + 2);

        // Mouse Cursor Position (red if clicked)
        ;
    }
};