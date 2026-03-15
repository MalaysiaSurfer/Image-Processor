#pragma once

#include "filter.h"
#include <vector>
#include <string>
#include <memory>

struct ParsedArgs {
    std::string input_path;
    std::string output_path;
    std::vector<std::unique_ptr<Filter>> filters;
};

ParsedArgs ParseArguments(int argc, char* argv[]);
void PrintHelp(const char* program_name);