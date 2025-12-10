/**
 * @file ui-manager.hpp
 * @authors MarioS271
 */

#pragma once

#include <algorithm>
#include <vector>
#include "type/event.hpp"
#include "class/panel.hpp"
#include "class/renderer.hpp"
#include "helper/colors.hpp"
#include "helper/anchors.hpp"

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

    void update() {
        bool redraw{true};

        if (anchor::right() < SHORT{60} ||
            anchor::bottom() < SHORT{20})
        { 
            redraw = false;

            COORD anchor = anchor::center();
            anchor.X -= SHORT{8};
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
        if (anchor::right() < SHORT{60} ||
            anchor::bottom() < SHORT{20})
        { 
            return;
        }

        switch (e.type) {
            case EventType::Mouse:
                for (auto p : panels) {
                    if (p->contains(e.mouse.position) || p->alwaysSendMouseEvent())
                        p->onMouse(e);
                }
                break;

            case EventType::Key:
                for (auto p : panels)
                    p->onKey(e);
                break;

            default:
                break;
        }
    }
};
