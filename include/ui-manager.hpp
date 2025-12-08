/**
 * @file ui-manager.hpp
 * @authors MarioS271
 */

#pragma once

#include <vector>
#include "panel.hpp"
#include "renderer.hpp"

class UIManager {
private:
    Renderer &renderer;
    std::vector<Panel*> panels;

public:
    UIManager(Renderer &r) : renderer(r) {}

    void addPanel(Panel* panel)
    {
        panels.push_back(panel);
    }

    void markDirty(Panel* panel) { panel->markDirty(); }

    void markAllDirty()
    {
        for (auto p : panels)
            p->markDirty();
    }

    void redraw()
    {
        bool redraw{true};

        if (screen::width() < static_cast<SHORT>(60) ||
            screen::height() < static_cast<SHORT>(20))
        { 
            redraw = false;
            renderer.clearArea(anchor::topLeft(), anchor::bottomRight());

            COORD anchor = anchor::center();
            anchor.X -= static_cast<SHORT>(8);
            renderer.drawText(anchor, L"Screen too small!", FOREGROUND_INTENSITY);
        }

        for (auto p : panels)
        {
            if (p->isDirty()) {
                if (redraw) p->redraw(renderer);
                p->clearDirty();
            }
        }
    }
};
