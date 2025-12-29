// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <cstdlib>

enum class Menu
{
    Main,
    Exit
};

extern Menu currentMenu;

inline void ClearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void DrawUI();
