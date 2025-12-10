/**
 * @file renderer.hpp
 * @authors MarioS271
 */

#pragma once

#include <string>
#include <windows.h>

class Renderer {
private:
    HANDLE hConsole;
    CONSOLE_CURSOR_INFO cursorInfo;

public:
    Renderer(HANDLE console);
    ~Renderer();

    void drawText(COORD pos, const std::wstring& text, WORD color);
    void drawRegion(COORD topLeft, COORD size, WORD color);
    void drawBox(COORD topLeft, COORD bottomRight, WORD color);

    void clearArea(COORD pos, COORD size, WORD color = 0x07);
};