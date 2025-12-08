/**
 * @file events.hpp
 * @authors MarioS271
 */

#pragma once

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
            bool pressed;
        } key;

        struct {
            short x, y;
            unsigned int buttonState;
        } mouse;

        struct {
            short width, height;
        } resize;
    };
};
