// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "Benchmark.hpp"
#include "Benchmark/MyJson.hpp"
#include "Benchmark/NlohmannJson.hpp"
#include "Benchmark/Simdjson.hpp"
#include "Benchmark/Yyjson.hpp"
#include "Generator.hpp"
#include "UI.hpp"
#include "Utils.hpp"
#include <filesystem>
#include <iostream>

Menu currentMenu = Menu::Main;

void DrawMainMenu()
{
    int generateJsonIdx = 0, benchmarkIdx = 0, singleLibIdx = 0, exitIdx = 0;
    int currentIdx = 1;

    std::cout << currentIdx << ". Generate big.json\n";
    generateJsonIdx = currentIdx++;
    if (std::filesystem::exists("big.json"))
    {
        std::cout << currentIdx << ". Benchmark libraries\n";
        benchmarkIdx = currentIdx++;
    }
    std::cout << currentIdx << ". Check a single library\n";
    singleLibIdx = currentIdx++;
    std::cout << currentIdx << ". Exit\n";
    exitIdx = currentIdx++;

    int input = 0;
    if (!(std::cin >> input))
    {
        ClearStdCin();
        return;
    }

    if (input == generateJsonIdx)
    {
        std::cout << "What size would you like big.json to be (in MB)?\n";
        int size;
        while (!(std::cin >> size))
        {
            ClearStdCin();
        }
        GenerateBigJson(size);
    }
    else if (input == benchmarkIdx)
    {
        auto result = RunBenchmarks();
        std::cout << result;
        std::cout << "Press Enter to continue...";
        ClearStdCin();
        std::cin.get();
    }
    else if (input == singleLibIdx)
        currentMenu = Menu::SingleLib;
    else if (input == exitIdx)
        currentMenu = Menu::Exit;
}

void DrawSingleLib()
{
    int backIdx = 0, nlohmannJsonIdx = 0, simdjsonIdx = 0, yyjsonIdx = 0, myJsonIdx = 0;
    int currentIdx = 1;

    std::cout << "Which library would you like to check?\n";
    std::cout << "0. Back\n";
    std::cout << currentIdx << ". nlohmann/json\n";
    nlohmannJsonIdx = currentIdx++;
    std::cout << currentIdx << ". simdjson\n";
    simdjsonIdx = currentIdx++;
    std::cout << currentIdx << ". yyjson\n";
    yyjsonIdx = currentIdx++;
    std::cout << currentIdx << ". my json\n";
    myJsonIdx = currentIdx++;

    int input = 0;
    if (!(std::cin >> input))
    {
        ClearStdCin();
        return;
    }

    if (input != backIdx) std::cout << "Benchmarking...\n";
    if (input == backIdx)
        currentMenu = Menu::Main;
    else if (input == nlohmannJsonIdx)
    {
        std::cout << "nlohmann/json took " << MeasureTime(RunNlohmannJson) << " seconds\n";
    }
    else if (input == simdjsonIdx)
    {
        std::cout << "simdjson took " << MeasureTime(RunSimdjson) << " seconds\n";
    }
    else if (input == yyjsonIdx)
    {
        std::cout << "yyjson took " << MeasureTime(RunYyjson) << " seconds\n";
    }
    else if (input == myJsonIdx)
    {
        std::cout << "my json took " << MeasureTime(RunMyJson) << " seconds\n";
    }
    std::cout << "Press Enter to continue...";
    ClearStdCin();
    std::cin.get();
    currentMenu = Menu::Main;
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
    case Menu::SingleLib:
        DrawSingleLib();
        break;
    default:
        break;
    }
}
