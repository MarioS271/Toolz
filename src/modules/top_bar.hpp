/**
 * @file top_bar.hpp
 * @authors MarioS271
 */

#include <array>
#include <windows.h>
#include "panel.hpp"
#include "screen.hpp"
#include "anchors.hpp"
#include "colors.hpp"
#include "constants.hpp"

class TopBar : public Panel {
public:
    void redraw(Renderer &r) override {
        WORD color = Colors::Fg::white | Colors::Fg::intense | Colors::Bg::blue | Colors::Bg::intense;
        WORD selColor = Colors::Fg::black | Colors::Bg::green | Colors::Bg::intense;

        COORD size = {
            screen::width(),
            (SHORT)1
        };
        r.clearArea(anchor::topLeft(), size);
        r.drawRegion(anchor::topLeft(), size, color);

        COORD drawPos = anchor::topLeft();
        std::array<std::wstring, 5> strs = {
            L"[Main Menu]",
            L"[System Info]",
            L"[Tasks]",
            L"[File Manager]",
            L"[Git Dash]",
        };
        for (SHORT i = 0; i < 5; i++) {
            r.drawText(drawPos, strs[i], state["sel_menu"] == i ? selColor : color);
            drawPos.X += static_cast<SHORT>(strs[i].length() + 1);
        }
    }

    bool onKey(const Event &k) override {
        SHORT previous = state["sel_menu"];

        switch (k.key.key) {
            case VK_F1: state["sel_menu"] = 0; break;
            case VK_F2: state["sel_menu"] = 1; break;
            case VK_F3: state["sel_menu"] = 2; break;
            case VK_F4: state["sel_menu"] = 3; break;
            case VK_F5: state["sel_menu"] = 4; break;
            default: break;
        }

        if (previous != state["sel_menu"]) {
            dirty = true;
            return true;
        }

        return false;
    }

    bool onMouse(const Event &m) override {
        COORD pos = m.mouse.position;
        SHORT previous = state["sel_menu"];

        if (m.mouse.buttonState != 1)
            return false;

        if (pos.X < 11)
            state["sel_menu"] = 0;
        else if (pos.X > 11 && pos.X < 25)
            state["sel_menu"] = 1;
        else if (pos.X > 25 && pos.X < 33)
            state["sel_menu"] = 2;
        else if (pos.X > 33 && pos.X < 46)
            state["sel_menu"] = 3;
        else if (pos.X > 46 && pos.X < 57)
            state["sel_menu"] = 4;

        if (previous != state["sel_menu"]) {
            dirty = true;
            return true;
        }

        return false;
    }

    bool contains(COORD coords) override {
        return coords.Y == anchor::topLeft().Y;
    }

    SHORT getCurrMenu() {
        return state["sel_menu"];
    }
};