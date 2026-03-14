#include "arg_parser.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "sharpening_filter.h"
#include "edgedetection_filter.h"
#include "crop_filter.h"
#include "gaussianblur_filter.h"
#include "twirl_filter.h"
#include <iostream>
#include <string>

void PrintHelp(const char* program_name) {
    std::cout << "Usage: " << program_name << " <input.bmp> <output.bmp> [filters...]\n\n"
              << "Available filters:\n"
              << "  -crop <width> <height>\n"
              << "  -gs\n"
              << "  -neg\n"
              << "  -sharp\n"
              << "  -edge <threshold>\n"
              << "  -blur <sigma>\n"
              << "  -twirl <radius> <angle>\n";
}

ParsedArgs ParseArguments(int argc, char* argv[]) {
    if (argc < 3) {
        PrintHelp(argv[0]);
        throw std::runtime_error("");
    }

    ParsedArgs args;
    args.input_path = argv[1];
    args.output_path = argv[2];

    int i = 3;
    while (i < argc) {
        std::string token = argv[i];
        if (token == "-gs") {
            args.filters.push_back(std::make_unique<GrayscaleFilter>());
            ++i;
        } else if (token == "-neg") {
            args.filters.push_back(std::make_unique<NegativeFilter>());
            ++i;
        } else if (token == "-sharp") {
            args.filters.push_back(std::make_unique<SharpeningFilter>());
            ++i;
        } else if (token == "-edge") {
            if (i + 1 >= argc) {
                throw std::runtime_error("-edge requires argument");
            }
            args.filters.push_back(std::make_unique<EdgeDetectionFilter>(std::stod(argv[i + 1])));
            i += 2;
        } else if (token == "-crop") {
            if (i + 2 >= argc) {
                throw std::runtime_error("-crop requires two arguments");
            }
            args.filters.push_back(std::make_unique<CropFilter>(std::stoul(argv[i + 1]), std::stoul(argv[i + 2])));
            i += 3;
        } else if (token == "-blur") {
            if (i + 1 >= argc) {
                throw std::runtime_error("-blur requires argument");
            }
            args.filters.push_back(std::make_unique<GaussianBlurFilter>(std::stod(argv[i + 1])));
            i += 2;
        } else if (token == "-twirl") {
            if (i + 2 >= argc) {
                throw std::runtime_error("-twirl requires two arguments");
            }
            args.filters.push_back(std::make_unique<TwirlFilter>(std::stod(argv[i + 1]), std::stod(argv[i + 2])));
            i += 3;
        } else {
            throw std::runtime_error("Unknown filter: " + token);
        }
    }
    return args;
}