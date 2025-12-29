// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "Benchmark/MyJson.hpp"
#include "Json.hpp"

void RunMyJson()
{
    Json json = Json::Load("big.json");
    json.Save("tmp.json");
}
