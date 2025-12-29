// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "Benchmark/NlohmannJson.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

void RunNlohmannJson()
{
    std::ifstream in("big.json");
    json data = json::parse(in);
    std::ofstream out("tmp.json");
    out << data.dump(4);
}
