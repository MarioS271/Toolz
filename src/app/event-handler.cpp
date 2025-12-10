/**
 * @file event-handler.cpp
 * @authors MarioS271
 */

#include "class/event-handler.hpp"

EventHandler::EventHandler(HANDLE input)
    : hInput(input)
{
    GetConsoleMode(hInput, &prevMode);

    mode |= ENABLE_EXTENDED_FLAGS;
    mode &= ~ENABLE_QUICK_EDIT_MODE;
    mode |= ENABLE_MOUSE_INPUT | ENABLE_WINDOW_INPUT;
    SetConsoleMode(hInput, mode);
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
                e.key.character = input.Event.KeyEvent.uChar.UnicodeChar;
                e.key.pressed = input.Event.KeyEvent.bKeyDown;
                e.key.controlState = input.Event.KeyEvent.dwControlKeyState;
                break;

            case MOUSE_EVENT:
                e.type = EventType::Mouse;
                e.mouse.position.X = input.Event.MouseEvent.dwMousePosition.X;
                e.mouse.position.Y = input.Event.MouseEvent.dwMousePosition.Y;
                e.mouse.buttonState = input.Event.MouseEvent.dwButtonState;
                e.mouse.controlState = input.Event.MouseEvent.dwControlKeyState;
                e.mouse.eventFlags = input.Event.MouseEvent.dwEventFlags;
                break;
                
            case WINDOW_BUFFER_SIZE_EVENT:
                e.type = EventType::Resize;
                break;
        }

        if (e.type != EventType::None) {
            for (auto &callback : listeners)
                callback(e);
        }
    }
}
