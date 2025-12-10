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
#include <iostream>

class BottomBar : public Panel {
private:
    struct State {
        COORD lastMousePos;
        bool mouseClicked;
        bool partRefresh;
    };
    State state = {0};
    State prevState = state;

public:
    void redraw(Renderer &r) override {
        using std::to_wstring;

        WORD color = Colors::Fg::white | Colors::Fg::intense | Colors::Bg::blue | Colors::Bg::intense;
        WORD mouseClickedColor = Colors::Fg::red | Colors::Fg::intense | Colors::Bg::blue | Colors::Bg::intense;
        
        COORD size{
            anchor::right(),
            SHORT{1},
        };

        std::wstring ver_text    = L"Toolz v" + std::wstring(constants::VERSION);
        std::wstring vw_res_text = to_wstring(anchor::right()) + L"x" + to_wstring(anchor::bottom());
        std::wstring cur_text    = to_wstring(state.lastMousePos.X) + L"," + to_wstring(state.lastMousePos.Y);

        COORD ver_drawPos = anchor::bottomLeft();

        COORD vw_res_drawPos = anchor::bottomRight();
        vw_res_drawPos.X -= static_cast<SHORT>(vw_res_text.length());
        
        COORD cur_drawPos = vw_res_drawPos;
        cur_drawPos.X -= static_cast<SHORT>(cur_text.length() + 2);

        COORD cur_fill_drawPos = cur_drawPos;
        cur_fill_drawPos.X -= 1;


        if (!partRefresh) {
            r.drawRegion(anchor::bottomLeft(), size, color);

            r.drawText(ver_drawPos, ver_text, color);
            r.drawText(vw_res_drawPos, vw_res_text, color);
        }

        if ((state.lastMousePos.X != prevState.lastMousePos.X ||
             state.lastMousePos.Y != prevState.lastMousePos.Y ||
             state.mouseClicked   != prevState.mouseClicked ||
             !partRefresh
            ) && constants::MOUSE_CLICK_INFO)
        {
            COORD cur_fill_drawPos;

            cur_fill_drawPos = cur_drawPos;
            cur_fill_drawPos.X -= 2;
            r.drawText(cur_fill_drawPos, L"  ", color);

            cur_fill_drawPos = cur_drawPos;
            cur_fill_drawPos.X += cur_text.length();
            r.drawText(cur_fill_drawPos, L"  ", color);

            r.drawText(cur_drawPos, cur_text, state.mouseClicked ? mouseClickedColor : color);
        }

        partRefresh = false;
        prevState = state;
    }

    void onMouse(const Event& m) override {
        if (constants::MOUSE_CLICK_INFO) {
            dirty = true;
            partRefresh = true;

            state.mouseClicked = static_cast<bool>(m.mouse.buttonState);
            state.lastMousePos = m.mouse.position;
        }
    }

    bool alwaysSendMouseEvent() override { return true; }
};