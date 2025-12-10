/**
 * @file event-handler.hpp
 * @authors MarioS271
 */

#pragma once

#include <vector>
#include <functional>
#include <windows.h>
#include "event.hpp"

class EventHandler {
public:
    using Callback = std::function<void(const Event&)>;

private:
    HANDLE hInput;
    DWORD prevMode;
    WORD mode;
    std::vector<Callback> listeners;

public:
    EventHandler(HANDLE input);
    ~EventHandler();

    void addListener(Callback cb);
    void pollEvents();

    WORD getMode() const { return mode; }
};
