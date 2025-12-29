// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

enum class Menu
{
    Main,
    Exit,
    SingleLib
};

extern Menu currentMenu;

void DrawUI();
