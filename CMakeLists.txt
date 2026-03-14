cmake_minimum_required(VERSION 3.15)
project(image_processor CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(
    image_processor
    src/image_processor.cpp
    src/image.cpp
    src/bmp.cpp
    src/grayscale_filter.cpp
    src/negative_filter.cpp
    src/sharpening_filter.cpp
    src/edgedetection_filter.cpp
    src/crop_filter.cpp
    src/gaussianblur_filter.cpp
    src/arg_parser.cpp
    src/twirl_filter.cpp
)
