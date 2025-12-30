// SPDX-FileCopyrightText: 2025 SemkiShow
//
// SPDX-License-Identifier: GPL-3.0-only

#include "Generator.hpp"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <random>

class JsonGenerator
{
    std::mt19937 rng;
    std::uniform_int_distribution<int> typeDist;
    std::uniform_int_distribution<int> boolDist;
    std::uniform_real_distribution<double> doubleDist;
    std::uniform_int_distribution<int> stringLengthDist;

    const std::string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
    int indentation = 0;
    int maxDepth = 10;

    void GetIndentation(std::string& buf) { buf.append(4 * indentation, ' '); }

  public:
    JsonGenerator()
        : rng(std::random_device{}()), typeDist(0, 4), boolDist(0, 1),
          doubleDist(-10000.0, 10000.0), stringLengthDist(5, 20)
    {
    }

    void IncreaseIndentation() { indentation++; }

    void DecreaseIndentation()
    {
        indentation--;
        indentation = fmax(0, indentation);
    }

    void RandomString(std::string& buf)
    {
        size_t len = stringLengthDist(rng);
        buf += "\"";
        for (size_t i = 0; i < len; i++)
            buf += charset[rng() % charset.size()];
        buf += "\"";
    }

    void GenerateValue(std::string& buf, int depth)
    {
        // Higher depth increases the chance of picking a primitive to avoid infinite recursion
        int type = depth > maxDepth ? (rand() % 3) : typeDist(rng);

        switch (type)
        {
        case 0:
            RandomString(buf);
            break;
        case 1:
            buf += std::to_string(doubleDist(rng));
            break;
        case 2:
            buf += (boolDist(rng) ? "true" : "false");
            break;
        case 3:
            GenerateArray(buf, depth + 1, false);
            break;
        case 4:
            GenerateObject(buf, depth + 1, false);
            break;
        }
    }

    void GenerateArray(std::string& buf, int depth, bool indentStart = true)
    {
        if (indentStart) GetIndentation(buf);
        buf += "[\n";
        IncreaseIndentation();
        int size = rng() % 10 + 1;
        for (int i = 0; i < size; i++)
        {
            GetIndentation(buf);
            GenerateValue(buf, depth);
            if (i < size - 1) buf += ",\n";
        }
        DecreaseIndentation();
        buf += "\n";
        GetIndentation(buf);
        buf += "]";
    }

    void GenerateObject(std::string& buf, int depth, bool indentStart = true)
    {
        if (indentStart) GetIndentation(buf);
        buf += "{\n";
        IncreaseIndentation();
        int size = rng() % 8 + 1;
        for (int i = 0; i < size; i++)
        {
            GetIndentation(buf);
            RandomString(buf);
            buf += ": ";
            GenerateValue(buf, depth);
            if (i < size - 1) buf += ",\n";
        }
        DecreaseIndentation();
        buf += "\n";
        GetIndentation(buf);
        buf += "}";
    }
};

void GenerateBigJson(float targetSizeMB)
{
    std::ofstream file("big.json");
    JsonGenerator gen;

    size_t chunkSize = 1024 * 1024;
    std::string chunk;
    chunk.reserve(chunkSize);
    size_t bytesWritten = 0;

    std::cout << "Generating a " << targetSizeMB << " MB big.json file...\n";

    chunk += "[\n";
    gen.IncreaseIndentation();
    while (bytesWritten + chunk.size() < targetSizeMB * 1024 * 1024)
    {
        gen.GenerateObject(chunk, 0);
        chunk += ",\n";

        if (chunk.size() > chunkSize)
        {
            file << chunk;
            bytesWritten += chunk.size();
            chunk.clear();

            float mbLeft = (targetSizeMB * 1024 * 1024 - bytesWritten) / 1024.0f / 1024;
            std::cout << std::fixed << std::setprecision(0) << mbLeft << " MB left          \r"
                      << std::flush;
        }
    }

    file << chunk;
    file.seekp(-2, std::ios_base::end); // Remove last comma

    gen.DecreaseIndentation();
    file << "\n]";
    file.close();
}
