#include "grayscale_filter.h"

const double R_GRAY = 0.299;
const double G_GRAY = 0.587;
const double B_GRAY = 0.114;

Image GrayscaleFilter::Apply(const Image& src) const {
    Image dst(src.GetWidth(), src.GetHeight());
    for (size_t y = 0; y < src.GetHeight(); ++y) {
        for (size_t x = 0; x < src.GetWidth(); ++x) {
            const Color& c = src.At(x, y);
            double gray = R_GRAY * c.r + G_GRAY * c.g + B_GRAY * c.b;
            dst.At(x, y) = Color(gray, gray, gray);
        }
    }
    return dst;
}
