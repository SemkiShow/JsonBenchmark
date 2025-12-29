// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "Generator.hpp"
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
    if (!(std::cin >> input))
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }

    if (input == generateJsonIdx) GenerateBigJson(1024);
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
