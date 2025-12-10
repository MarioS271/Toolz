/**
 * @file panel.hpp
 * @authors MarioS271
 */

#pragma once

#include <windows.h>
#include "type/event.hpp"
#include "class/renderer.hpp"

class Panel {
protected:
    bool dirty{true};

public:
    virtual ~Panel() = default;

    virtual void redraw(Renderer& renderer) = 0;

    virtual bool onMouse(const Event& m) { return false; }
    virtual bool onKey(const Event& k) { return false; }

    virtual bool contains(COORD coords) { return false; }

    void markDirty() { dirty = true; }
    bool isDirty() const { return dirty; }
    void clearDirty() { dirty = false; }
};