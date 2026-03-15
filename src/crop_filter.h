#pragma once

#include "filter.h"

class CropFilter : public Filter {
public:
    explicit CropFilter(size_t width, size_t height) : width_(width), height_(height) {
    }
    Image Apply(const Image& src) const override;

private:
    size_t width_;
    size_t height_;
};