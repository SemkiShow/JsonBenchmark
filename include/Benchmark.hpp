// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#pragma once

#include <ostream>
struct BenchmarkResult
{
    float nlohmannJsonTime = 0, simdjsonTime = 0, yyjsonTime = 0, myJsonTime = 0;
};

inline std::ostream& operator<<(std::ostream& out, const BenchmarkResult& result)
{
    out << "nlohmann/json took " << result.nlohmannJsonTime << " seconds\n";
    out << "simdjson took " << result.simdjsonTime << " seconds\n";
    out << "yyjson took " << result.yyjsonTime << " seconds\n";
    out << "my json took " << result.myJsonTime << " seconds\n";
    return out;
}

BenchmarkResult RunBenchmarks();
