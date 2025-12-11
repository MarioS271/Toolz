/**
 * @file dashboard.hpp
 * @authors MarioS271
*/

#pragma once

#include <array>
#include <windows.h>
#include <secext.h>
#include "class/panel.hpp"
#include "helper/anchors.hpp"
#include "helper/colors.hpp"
#include "helper/clear_main.hpp"
#include "helper/short_cast.hpp"
#include "constants.hpp"

class DashPanel : public Panel {
public:
    void redraw(Renderer &r) override {
        using std::to_wstring;

        clearMain(r);

        WORD color = Colors::Fg::white | Colors::Fg::intense | Colors::Bg::black;

        DWORD size = 256, trueSize = 0;
        wchar_t buffer[size];
        std::wstring userName;

        GetUserNameExW(NameDisplay, buffer, &size);
        for (SHORT i = 0; i < size; ++i) {
            if (buffer[i] <= 0x7F)
                userName += buffer[i];
        }
        std::wstring welcome_text = L"Welcome, " + userName;
        welcome_text.erase(welcome_text.find_last_not_of(L" \t\n\r\f\v") + 1);


        SHORT paddingX = 1;
        SHORT paddingY = 1;
        SHORT boxWidth = scast(welcome_text.length()) + 2 * paddingX;
        COORD topLeft = {
            scast(anchor::center().X - boxWidth / 2 - 1),
            scast(anchor::center().Y / 2 - paddingY),
        };
        COORD bottomRight = {
            scast(topLeft.X + boxWidth + 1),
            scast(anchor::center().Y / 2 + paddingY),
        };
        r.drawBox(topLeft, bottomRight, color);

        r.drawText(
            {
                scast(anchor::center().X - (welcome_text.length() / 2)),
                scast(anchor::center().Y / 2),
            },
            welcome_text,
            color
        );
    }

    void onMouse(const Event& m) {
        COORD pos = m.mouse.position;

        if (m.mouse.buttonState != 1) {

        }
    }
};