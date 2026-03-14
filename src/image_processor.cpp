#include "arg_parser.h"
#include "bmp.h"
#include "image.h"
#include "grayscale_filter.h"
#include "negative_filter.h"
#include "sharpening_filter.h"
#include "edgedetection_filter.h"
#include "crop_filter.h"
#include "gaussianblur_filter.h"
#include <iostream>

int main(int argc, char** argv) {
    try {
        ParsedArgs args = ParseArguments(argc, argv);
        Image image = LoadBMP(args.input_path);
        for (auto& filter : args.filters) {
            auto& filter_instance = *filter;
            image = filter_instance.Apply(image);
        }
        SaveBMP(image, args.output_path);
    } catch (const std::runtime_error& e) {
        std::cerr << e.what() << std::endl;
        return 1;
    }
    return 0;
}
