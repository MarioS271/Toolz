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

    void addPanel(Panel* panel) {
        panels.push_back(panel);
    }

    /**
     * @brief Mark a specific panel as dirty
     *
     * @return void
     *
     * @param panel The panel to mark as dirty
     */
    void markDirty(Panel* panel) { panel->markDirty(); }

    /**
     * @brief Mark all panels as dirty (redraw)
     *
     * @return void
     */
    void markAllDirty() {
        for (auto p : panels)
            p->markDirty();
    }

    /**
     * @brief Redraw all dirty panels
     *
     * @return void
     */
    void redraw() {
        for (auto p : panels) {
            if (p->isDirty()) {
                p->redraw(renderer);
                p->clearDirty();
            }
        }
    }
};
