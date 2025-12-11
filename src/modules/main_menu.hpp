/**
 * @file main_menu.hpp
 * @authors MarioS271
 */

#pragma once

#include <array>
#include <windows.h>
#include "class/panel.hpp"
#include "helper/anchors.hpp"
#include "helper/colors.hpp"
#include "helper/clear_main.hpp"
#include "helper/short_cast.hpp"
#include "constants.hpp"

class MainPanel : public Panel {
private:
    static constexpr SHORT NUM_MENU_ITEMS = 5;
    static constexpr SHORT ITEM_SPACING = 1;

    const std::array<std::wstring, NUM_MENU_ITEMS> menuText = {
        L"   System Info   ",
        L"  Task Overview  ",
        L"  File Manager   ",
        L"  Git Dashboard  ",
        L"   Exit Toolz    ",
    };
    std::array<COORD, NUM_MENU_ITEMS> menuPos = {0};

public:
    void redraw(Renderer &r) override {
        clearMain(r);

        WORD color = Colors::Bg::white | Colors::Bg::intense | Colors::Fg::black;
        
        COORD c = anchor::center();
        menuPos = {
            COORD{scast(c.X - (menuText[0].length() / 2)), scast(c.Y - 2*ITEM_SPACING * 2)},
            COORD{scast(c.X - (menuText[1].length() / 2)), scast(c.Y - 2*ITEM_SPACING)},
            COORD{scast(c.X - (menuText[2].length() / 2)), scast(c.Y)},
            COORD{scast(c.X - (menuText[3].length() / 2)), scast(c.Y + 2*ITEM_SPACING)},
            COORD{scast(c.X - (menuText[4].length() / 2)), scast(c.Y + 2*ITEM_SPACING * 2)},
        };

        for (int i = 0; i < NUM_MENU_ITEMS; i++) {
            r.drawText(menuPos[i], menuText[i], color);
        }
    }

    void onMouse(const Event& m) {
        COORD pos = m.mouse.position;

        if (m.mouse.buttonState != 1) {
            
        }
    }
};