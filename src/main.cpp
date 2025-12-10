/**
 * @file main.cpp
 * @authors MarioS271
 */

#include <string>
#include <array>
#include <windows.h>

#include "constants.hpp"

#include "class/renderer.hpp"
#include "class/ui-manager.hpp"
#include "class/event-handler.hpp"

#include "helper/clearMain.hpp"

#include "modules/bars/top.hpp"
#include "modules/bars/bottom.hpp"
#include "modules/main_menu.hpp"
#include "modules/system.hpp"
#include "modules/tasks.hpp"
#include "modules/files.hpp"
#include "modules/git.hpp"


int main() {
    SetConsoleTitleA("Toolz");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    HANDLE hInput = GetStdHandle(STD_INPUT_HANDLE);
    
    Renderer renderer(hConsole);
    UIManager ui(renderer);
    EventHandler events(hInput);


    TopBar pn_topbar;
    BottomBar pn_bottombar;
    MainPanel pn_main;
    SystemPanel pn_system;
    TasksPanel pn_tasks;
    FilesPanel pn_files;
    GitPanel pn_git;
    
    ui.loadPanel(&pn_topbar);
    ui.loadPanel(&pn_bottombar);
    ui.loadPanel(&pn_main);
    
    
    bool running = true;
    SHORT currMenu = 0, currMenuPrev = 0;
    
    events.addListener([&](const Event &e){
        if (e.type == EventType::Key && e.key.pressed && e.key.key == VK_ESCAPE)
        running = false;
    });
    
    events.addListener([&](const Event &e){
        if (e.type == EventType::Resize) {
            system("cls");
            ui.markAllDirty();
            SetConsoleMode(hInput, events.getMode());
        }
    });
    
    events.addListener([&](const Event &e){
        ui.dispatchEvent(e);
    });
    
    while (running) {
        currMenuPrev = currMenu;
        currMenu = pn_topbar.getCurrMenu();
        
        if (currMenu != currMenuPrev) {
            ui.unloadPanel(&pn_main);
            ui.unloadPanel(&pn_system);
            ui.unloadPanel(&pn_tasks);
            ui.unloadPanel(&pn_files);
            ui.unloadPanel(&pn_git);

            clearMain(renderer);

            switch (currMenu) {
                case 0: ui.loadPanel(&pn_main); break;
                case 1: ui.loadPanel(&pn_system); break;
                case 2: ui.loadPanel(&pn_tasks); break;
                case 3: ui.loadPanel(&pn_files); break;
                case 4: ui.loadPanel(&pn_git); break;
                default: break;
            }
        }

        events.pollEvents();
        ui.update();

        Sleep(1000 / constants::FRAMERATE);
    }

    return 0;
}