/**
 * @file main.cpp
 * @authors MarioS271
 */

#include <windows.h>

#include "constants.hpp"

#include "anchors.hpp"
#include "screen.hpp"

#include "panel.hpp"
#include "ui-manager.hpp"
#include "renderer.hpp"

#include "event-handler.hpp"
#include "event.hpp"

class TopBar : public Panel {
public:
    void redraw(Renderer &r) override {
        COORD size = {
            screen::width(),
            static_cast<SHORT>(1)
        };

        WORD color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

        r.drawRegion(anchor::topLeft(), size, color);
        r.drawText(anchor::topLeft(), L"[Main Menu] [System Info] [Tasks] [File Manager] [Git Dash]", color);
    }
};

class MainPanel : public Panel {
public:
    void redraw(Renderer &r) override {
        COORD pos = anchor::center();
        pos.X -= 5;

        r.drawText(pos, L"Main Content", FOREGROUND_INTENSITY | FOREGROUND_RED);
    }
};

class BottomBar : public Panel {
public:
    void redraw(Renderer &r) override {
        COORD size = {
            screen::width(),
            static_cast<SHORT>(1)
        };

        WORD color = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE;

        r.drawRegion(anchor::bottomLeft(), size, color);

        std::wstring text = L"Toolz v" + std::wstring(constants::VERSION);
        r.drawText(anchor::bottomLeft(), text, color);
    }
};

int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    Renderer renderer(hConsole);
    UIManager ui(renderer);

    EventHandler events(hInput);

    DWORD mode;
    GetConsoleMode(hInput, &mode);
    SetConsoleMode(hInput,
        ENABLE_WINDOW_INPUT |
        ENABLE_MOUSE_INPUT |
        ENABLE_EXTENDED_FLAGS
    );

    TopBar top;
    BottomBar bottom;
    MainPanel main;

    ui.addPanel(&top);
    ui.addPanel(&bottom);
    ui.addPanel(&main);

    bool running = true;

    events.addListener([&](const Event &e){
        if (e.type == EventType::Key && e.key.pressed && e.key.key == VK_ESCAPE)
            running = false;

        if (e.type == EventType::Resize) {
            renderer.clearArea(anchor::topLeft(), anchor::bottomRight());
            ui.markAllDirty();
        }
    });

    while (running) {
        events.pollEvents();
        ui.redraw();
        Sleep(static_cast<DWORD>(1000 / constants::FRAMERATE));
    }

    renderer.clearArea(anchor::topLeft(), anchor::bottomRight());
    SetConsoleMode(hInput, mode);
    return 0;
}
