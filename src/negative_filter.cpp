#include "negative_filter.h"

Image NegativeFilter::Apply(const Image& src) const {
    Image dst(src.GetWidth(), src.GetHeight());
    for (size_t y = 0; y < src.GetHeight(); ++y) {
        for (size_t x = 0; x < src.GetWidth(); ++x) {
            const Color& c = src.At(x, y);
            dst.At(x, y) = Color(1 - c.r, 1 - c.g, 1 - c.b);
        }
    }
    return dst;
}