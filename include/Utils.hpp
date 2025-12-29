// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <chrono>
#include <functional>
#include <iostream>

class Timer
{
    std::chrono::time_point<std::chrono::high_resolution_clock> start;

  public:
    Timer() : start(std::chrono::high_resolution_clock::now()) {}

    double GetTimePassed()
    {
        auto end = std::chrono::high_resolution_clock::now();
        return std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1e6;
    }
};

inline double MeasureTime(std::function<void()> func)
{
    Timer timer;
    func();
    return timer.GetTimePassed();
}

inline void ClearConsole()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

inline void ClearStdCin()
{
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
