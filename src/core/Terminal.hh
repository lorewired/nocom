#pragma once

#include <windows.h>
#include <iostream>

namespace Game::Terminal {
    extern HANDLE hConsole;

    void HideCursor();
    void PositionCursor(int x, int y);
    void CleanScreen();
}