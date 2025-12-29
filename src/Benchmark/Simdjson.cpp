// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "Benchmark/Simdjson.hpp"
#include <fstream>
#include <simdjson.h>
using namespace simdjson;

void RunSimdjson()
{
    dom::parser parser;
    dom::element doc = parser.load("big.json");
    std::ofstream out("tmp.json");
    out << prettify(doc);
}
