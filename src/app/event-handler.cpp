/**
 * @file event-handler.cpp
 * @authors MarioS271
 */

#include "event-handler.hpp"

EventHandler::EventHandler(HANDLE input)
    : hInput(input)
{
    GetConsoleMode(hInput, &prevMode);
    SetConsoleMode(hInput,
        ENABLE_EXTENDED_FLAGS |
        ENABLE_MOUSE_INPUT |
        ENABLE_WINDOW_INPUT);
}

EventHandler::~EventHandler() {
    SetConsoleMode(hInput, prevMode);
}

void EventHandler::addListener(Callback cb) {
    listeners.push_back(cb);
}

void EventHandler::pollEvents() {
    DWORD eventsAvailable;
    INPUT_RECORD input;

    while (true) {
        if (!PeekConsoleInput(hInput, &input, 1, &eventsAvailable) || eventsAvailable == 0)
            break;

        DWORD eventsRead;
        ReadConsoleInput(hInput, &input, 1, &eventsRead);

        Event e{EventType::None};
        switch (input.EventType) {
            case KEY_EVENT:
                e.type = EventType::Key;
                e.key.key = input.Event.KeyEvent.wVirtualKeyCode;
                e.key.pressed = input.Event.KeyEvent.bKeyDown;
                break;
            case MOUSE_EVENT:
                e.type = EventType::Mouse;
                e.mouse.x = input.Event.MouseEvent.dwMousePosition.X;
                e.mouse.y = input.Event.MouseEvent.dwMousePosition.Y;
                e.mouse.buttonState = input.Event.MouseEvent.dwButtonState;
                break;
            case WINDOW_BUFFER_SIZE_EVENT:
                e.type = EventType::Resize;
                e.resize.width = input.Event.WindowBufferSizeEvent.dwSize.X;
                e.resize.height = input.Event.WindowBufferSizeEvent.dwSize.Y;
                break;
        }

        if (e.type != EventType::None) {
            for (auto &cb : listeners)
                cb(e);
        }
    }
}
