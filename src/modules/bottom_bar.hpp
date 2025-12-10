/**
 * @file bottom_bar.hpp
 * @authors MarioS271
 */

#include <windows.h>
#include "panel.hpp"
#include "screen.hpp"
#include "anchors.hpp"
#include "colors.hpp"
#include "constants.hpp"

class BottomBar : public Panel {
public:
    void redraw(Renderer &r) override {
        WORD color = Colors::Fg::white | Colors::Fg::intense | Colors::Bg::blue | Colors::Bg::intense;

        COORD size = {
            screen::width(),
            (SHORT)1
        };
        r.drawRegion(anchor::bottomLeft(), size, color);

        COORD drawPos = anchor::bottomLeft();
        std::wstring text{L""};

        // Version
        text = L"Toolz v" + std::wstring(constants::VERSION);
        r.drawText(drawPos, text, color);
        drawPos.X += static_cast<SHORT>(text.length() + 2);

        // Viewport Resolution
        text = std::to_wstring(screen::width()) + L"x" + std::to_wstring(screen::height());
        r.drawText(drawPos, text, color);
        drawPos.X += static_cast<SHORT>(text.length() + 2);
    }
};