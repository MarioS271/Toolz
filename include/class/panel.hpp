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
    bool dirty = true;
    bool partRefresh = false;

public:
    virtual ~Panel() = default;

    virtual void redraw(Renderer& renderer) = 0;

    virtual void onMouse(const Event& m) {}
    virtual void onKey(const Event& k) {}

    virtual bool contains(COORD coords) { return false; }
    virtual bool alwaysSendMouseEvent() { return false; }

    void markDirty() { dirty = true; }
    bool isDirty() const { return dirty; }
    void clearDirty() { dirty = false; }
};