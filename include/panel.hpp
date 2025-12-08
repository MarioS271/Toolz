/**
 * @file panel.hpp
 * @authors MarioS271
 */

#pragma once

#include "renderer.hpp"

class Panel {
protected:
    bool dirty{true};

public:
    virtual ~Panel() = default;
    virtual void redraw(Renderer &renderer) = 0;

    /**
     * @brief Marks panel as dirty
     *
     * @return void
     */
    void markDirty() { dirty = true; }

    /**
     * @brief Checks if panel is dirty
     *
     * @return bool
     */
    bool isDirty() const { return dirty; }

    /**
     * @brief Clear panel from dirty state
     *
     * @return void
     */
    void clearDirty() { dirty = false; }
};