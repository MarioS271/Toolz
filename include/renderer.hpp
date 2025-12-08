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

    /**
     * @brief Draws some Text
     *
     * @return void
     *
     * @param pos Position to start drawing at
     * @param text Text to draw
     * @param color Color to use when drawing text
     */
    void drawText(COORD pos, const std::wstring& text, WORD color);

    void drawRegion(COORD topLeft, COORD size, WORD color);
    void drawBox(COORD topLeft, COORD bottomRight, WORD color);

    /**
     * @brief Clears an area in the terminal
     *
     * @return void
     *
     * @param pos The position to start clearing from
     * @param size How far to clear from pos
     * @param color The color to clear with (default is 0x07)
     */
    void clearArea(COORD pos, COORD size, WORD color = 0x07);
};