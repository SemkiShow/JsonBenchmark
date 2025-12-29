// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "UI.hpp"

int main()
{
    while (currentMenu != Menu::Exit)
    {
        DrawUI();
    }

    return 0;
}
