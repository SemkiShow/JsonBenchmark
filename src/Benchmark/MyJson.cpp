// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "Benchmark/MyJson.hpp"
#include "JSON.hpp"

void RunMyJson()
{
    JSON json = JSON::Load("big.json");
    json.Save("tmp.json");
}
