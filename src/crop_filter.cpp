#include "crop_filter.h"

Image CropFilter::Apply(const Image& src) const {
    size_t new_w = std::min(src.GetWidth(), width_);
    size_t new_h = std::min(src.GetHeight(), height_);
    Image dst(new_w, new_h);
    for (size_t y = 0; y < new_h; ++y) {
        for (size_t x = 0; x < new_w; ++x) {
            dst.At(x, y) = src.At(x, y);
        }
    }
    return dst;
}