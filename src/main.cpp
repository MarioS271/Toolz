/**
 * @file main.cpp
 * @authors MarioS271
 */

#include <string>
#include <array>
#include <unordered_map>
#include <windows.h>

#include "constants.hpp"

#include "ui-manager.hpp"
#include "renderer.hpp"

#include "event-handler.hpp"

#include "modules/top_bar.hpp"
#include "modules/bottom_bar.hpp"
#include "modules/main_menu.hpp"
#include "modules/git.hpp"


int main() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);

    Renderer renderer(hConsole);
    UIManager ui(renderer);

    EventHandler events(hInput);

    TopBar pn_top;
    BottomBar pn_bottom;
    MainPanel pn_main;
    GitPanel pn_git;

    ui.loadPanel(&pn_top);
    ui.loadPanel(&pn_bottom);
    ui.loadPanel(&pn_main);

    bool running = true;

    events.addListener([&](const Event &e){
        if (e.type == EventType::Key && e.key.pressed && e.key.key == VK_ESCAPE)
            running = false;

        if (e.type == EventType::Resize) {
            system("cls");
            ui.markAllDirty();
            SetConsoleMode(hInput, events.getMode());
        }

        ui.dispatchEvent(e);
    });

    SHORT currMenu{0}, currMenuPrev{0};
    while (running) {
        currMenuPrev = currMenu;
        currMenu = pn_top.getCurrMenu();

        if (currMenu != currMenuPrev) {
            ui.unloadPanel(&pn_main);
            ui.unloadPanel(&pn_git);

            ui.clearCenterArea();

            switch (currMenu) {
                case 0: ui.loadPanel(&pn_main); break;
                case 1: break;
                case 2: break;
                case 3: break;
                case 4: ui.loadPanel(&pn_git); break;
                default: break;
            }
        }

        events.pollEvents();
        ui.redraw();
        Sleep(static_cast<DWORD>(1000 / constants::FRAMERATE));
    }

    return 0;
}