#pragma once

#include <windows.h>

namespace ConsoleColors {
    enum Color {
        RESET = 7,  
        RED = 12,
        GREEN = 10,
        YELLOW = 14,
        BLUE = 9,
        MAGENTA = 13,
        CYAN = 11,
        WHITE = 15,
        BOLD = 15 
    };

    void setColor(Color color) {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color);
    }

    void resetColor() {
        setColor(RESET);
    }
}