/**
 * @file renderer.cpp
 * @authors MarioS271
 */

#include "class/renderer.hpp"
#include "helper/anchors.hpp"
#include "helper/short_cast.hpp"

Renderer::Renderer(HANDLE console)
    : hConsole(console)
{
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = FALSE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    system("cls");
}

Renderer::~Renderer() {
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = TRUE;
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    system("cls");
}

void Renderer::drawText(COORD pos, const std::wstring& text, WORD color) {
    DWORD written;
    FillConsoleOutputAttribute(hConsole, color, text.size(), pos, &written);
    WriteConsoleOutputCharacterW(hConsole, text.c_str(), text.size(), pos, &written);
}

void Renderer::drawRegion(COORD topLeft, COORD size, WORD color) {
    DWORD written;
    int cellCount = size.X * size.Y;
    FillConsoleOutputCharacterW(hConsole, L' ', cellCount, topLeft, &written);
    FillConsoleOutputAttribute(hConsole, color, cellCount, topLeft, &written);
}

void Renderer::drawBox(COORD topLeft, COORD bottomRight, WORD color) {
    DWORD written;
    int width = bottomRight.X - topLeft.X + 1;
    int height = bottomRight.Y - topLeft.Y + 1;

    std::wstring horizontal(width, L'─');
    COORD posTop = topLeft;
    COORD posBottom = {topLeft.X, bottomRight.Y};

    FillConsoleOutputAttribute(hConsole, color, width, posTop, &written);
    WriteConsoleOutputCharacterW(hConsole, horizontal.c_str(), width, posTop, &written);

    FillConsoleOutputAttribute(hConsole, color, width, posBottom, &written);
    WriteConsoleOutputCharacterW(hConsole, horizontal.c_str(), width, posBottom, &written);

    for (int y = 1; y < height - 1; ++y) {
        COORD posLeft = {topLeft.X, scast(topLeft.Y + y)};
        COORD posRight = {bottomRight.X, scast(topLeft.Y + y)};
        FillConsoleOutputAttribute(hConsole, color, 1, posLeft, &written);
        WriteConsoleOutputCharacterW(hConsole, L"│", 1, posLeft, &written);

        FillConsoleOutputAttribute(hConsole, color, 1, posRight, &written);
        WriteConsoleOutputCharacterW(hConsole, L"│", 1, posRight, &written);
    }

    WriteConsoleOutputCharacterW(hConsole, L"┌", 1, topLeft, &written);
    WriteConsoleOutputCharacterW(hConsole, L"┐", 1, {bottomRight.X, topLeft.Y}, &written);
    WriteConsoleOutputCharacterW(hConsole, L"└", 1, {topLeft.X, bottomRight.Y}, &written);
    WriteConsoleOutputCharacterW(hConsole, L"┘", 1, bottomRight, &written);
}

void Renderer::clearArea(COORD pos, COORD size, WORD color) {
    DWORD written;
    int cellCount = size.X * size.Y;
    FillConsoleOutputCharacterW(hConsole, L' ', cellCount, pos, &written);
    FillConsoleOutputAttribute(hConsole, color, cellCount, pos, &written);
}