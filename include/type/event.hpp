/**
 * @file events.hpp
 * @authors MarioS271
 */

#pragma once

#include <windows.h>

enum class EventType {
    Key,
    Mouse,
    Resize,
    None
};

struct Event {
    EventType type;
    union {
        struct {
            unsigned short key;
            wchar_t character;
            bool pressed;
            unsigned int controlState;
        } key;

        struct {
            COORD position;
            unsigned int buttonState;
            unsigned int controlState;
            unsigned int eventFlags;
        } mouse;
    };
};
