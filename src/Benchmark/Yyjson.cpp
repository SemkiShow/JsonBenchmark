// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "Benchmark/Yyjson.hpp"
#include <fstream>
#include <yyjson.h>

void RunYyjson()
{
    yyjson_doc* doc = yyjson_read_file("big.json", 0, NULL, NULL);
    yyjson_mut_doc* mut_doc = yyjson_doc_mut_copy(doc, NULL);
    std::ofstream out("tmp.json");
    out << yyjson_mut_write(mut_doc, 0, NULL);
}
