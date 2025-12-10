/**
 * @file ui-manager.hpp
 * @authors MarioS271
 */

#pragma once

#include <algorithm>
#include <vector>
#include "panel.hpp"
#include "renderer.hpp"
#include "event.hpp"
#include "screen.hpp"
#include "colors.hpp"
#include "anchors.hpp"

class UIManager {
private:
    Renderer &renderer;
    std::vector<Panel*> panels;

public:
    UIManager(Renderer &r) : renderer(r) {}

    void loadPanel(Panel* panel) {
        panels.push_back(panel);
        panel->markDirty();
    }

    void unloadPanel(Panel* panel) {
        auto it = std::find(panels.begin(), panels.end(), panel);
        if (it != panels.end()) {
            panels.erase(it);
        }
    }

    void markDirty(Panel* panel) { panel->markDirty(); }

    void markAllDirty() {
        for (auto p : panels)
            p->markDirty();
    }

    void redraw() {
        bool redraw{true};

        if (screen::width() < (SHORT)60 ||
            screen::height() < (SHORT)20)
        { 
            redraw = false;

            COORD anchor = anchor::center();
            anchor.X -= static_cast<SHORT>(8);
            renderer.drawText(anchor, L"Screen too small!", Colors::Fg::white);
        }

        if (redraw) {
            for (auto p : panels) {
                if (p->isDirty()) {
                    p->redraw(renderer);
                    p->clearDirty();
                }
            }
        }
    }

    void dispatchEvent(const Event& e) {
        switch (e.type) {
            case EventType::Mouse: {
                for (auto it = panels.rbegin(); it != panels.rend(); ++it) {
                    Panel* p = *it;

                    if (p->contains(e.mouse.position)) {
                        if (p->onMouse(e))
                            return;
                    }
                }
            }

            case EventType::Key:
                for (auto p : panels)
                    if (p->onKey(e)) return;
                break;

            default:
                break;
        }
    }

    void clearCenterArea() {
        COORD size = {
            screen::width(),
            static_cast<SHORT>(screen::height() - 2),
        };
        COORD anchor_lu = {
            anchor::topLeft().X,
            static_cast<SHORT>(anchor::topLeft().Y + 1),
        };
        renderer.clearArea(anchor_lu, size);
    }
};
