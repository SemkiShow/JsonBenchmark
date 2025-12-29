// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "UI.hpp"
#include <filesystem>
#include <iostream>

Menu currentMenu = Menu::Main;

void DrawMainMenu()
{
    int generateJsonIdx = 0, benchmarkIdx = 0, exitIdx = 0;
    int currentIdx = 1;

    std::cout << currentIdx << ". Generate big.json\n";
    generateJsonIdx = currentIdx++;
    if (std::filesystem::exists("big.json"))
    {
        std::cout << currentIdx << ". Benchmark libraries\n";
        benchmarkIdx = currentIdx++;
    }
    std::cout << currentIdx << ". Exit\n";
    exitIdx = currentIdx++;

    int input = 0;
    std::cin >> input;

    if (input == generateJsonIdx)
        ;
    if (input == benchmarkIdx)
        ;
    if (input == exitIdx) currentMenu = Menu::Exit;
}

void DrawUI()
{
    ClearConsole();
    switch (currentMenu)
    {
    case Menu::Main:
        DrawMainMenu();
        break;
    case Menu::Exit:
        return;
        break;
    default:
        break;
    }
}
