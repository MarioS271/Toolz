/**
 * @file panel.hpp
 * @authors MarioS271
 */

#pragma once

#include <unordered_map>
#include <windows.h>
#include "renderer.hpp"
#include "event.hpp"

class Panel {
protected:
    bool dirty{true};

    std::unordered_map<std::string, SHORT> state;

public:
    virtual ~Panel() = default;

    virtual void redraw(Renderer &renderer) = 0;

    virtual bool onMouse(const Event &m) { return false; }
    virtual bool onKey(const Event &k) { return false; }

    virtual bool contains(COORD coords) { return false; }

    void markDirty() { dirty = true; }
    bool isDirty() const { return dirty; }
    void clearDirty() { dirty = false; }
};