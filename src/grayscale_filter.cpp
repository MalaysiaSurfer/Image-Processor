#include "grayscale_filter.h"

Image GrayscaleFilter::Apply(const Image& src) const {
    Image dst(src.GetWidth(), src.GetHeight());
    for (size_t y = 0; y < src.GetHeight(); ++y) {
        for (size_t x = 0; x < src.GetWidth(); ++x) {
            const Color& c = src.At(x, y);
            double gray = 0.299 * c.r + 0.587 * c.g + 0.114 * c.b;
            dst.At(x, y) = Color(gray, gray, gray);
        }
    }
    return dst;
}