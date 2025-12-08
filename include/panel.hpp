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

    void markDirty() { dirty = true; }
    bool isDirty() const { return dirty; }
    void clearDirty() { dirty = false; }
};