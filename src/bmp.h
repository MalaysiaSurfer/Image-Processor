#pragma once

#include "image.h"
#include <string>

Image LoadBMP(const std::string& path);
void SaveBMP(const Image& image, const std::string& path);
