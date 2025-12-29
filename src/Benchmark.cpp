// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "Benchmark.hpp"
#include "Benchmark/MyJson.hpp"
#include "Benchmark/NlohmannJson.hpp"
#include "Benchmark/Simdjson.hpp"
#include "Benchmark/Yyjson.hpp"
#include "Utils.hpp"

BenchmarkResult RunBenchmarks()
{
    BenchmarkResult result;

    std::cout << "Benchmarking nlohmann/json...\n";
    result.nlohmannJsonTime = MeasureTime(RunNlohmannJson);

    std::cout << "Benchmarking simdjson...\n";
    result.simdjsonTime = MeasureTime(RunSimdjson);

    std::cout << "Benchmarking yyjson...\n";
    result.yyjsonTime = MeasureTime(RunYyjson);

    std::cout << "Benchmarking my json...\n";
    result.myJsonTime = MeasureTime(RunMyJson);

    return result;
}
