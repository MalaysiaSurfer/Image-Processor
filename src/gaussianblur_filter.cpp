#include "gaussianblur_filter.h"

#include <cmath>
#include <vector>

Image GaussianBlurFilter::Apply(const Image& src) const {
    int radius = static_cast<int>(std::ceil(3.0 * sigma_));
    size_t kernel_size = static_cast<size_t>(2 * radius + 1);
    std::vector<double> kernel(kernel_size);

    double sum = 0.0;
    for (size_t i = 0; i < kernel_size; ++i) {
        int d = static_cast<int>(i) - radius;
        kernel[i] = std::exp(-(d * d) / (2.0 * sigma_ * sigma_));
        sum += kernel[i];
    }
    for (auto& v : kernel) {
        v /= sum;
    }

    Image tmp(src.GetWidth(), src.GetHeight());
    for (size_t y = 0; y < src.GetHeight(); ++y) {
        for (size_t x = 0; x < src.GetWidth(); ++x) {
            double r = 0.0, g = 0.0, b = 0.0;
            for (size_t k = 0; k < kernel_size; ++k) {
                int sx = static_cast<int>(x) + static_cast<int>(k) - radius;
                const Color& c = src.SafeAt(sx, static_cast<int>(y));
                r += c.r * kernel[k];
                g += c.g * kernel[k];
                b += c.b * kernel[k];
            }
            tmp.At(x, y) = Color(r, g, b);
        }
    }

    Image dst(tmp.GetWidth(), tmp.GetHeight());
    for (size_t x = 0; x < tmp.GetWidth(); ++x) {
        for (size_t y = 0; y < tmp.GetHeight(); ++y) {
            double r = 0.0, g = 0.0, b = 0.0;
            for (size_t k = 0; k < kernel_size; ++k) {
                int sy = static_cast<int>(y) + static_cast<int>(k) - radius;
                const Color& c = tmp.SafeAt(static_cast<int>(x), sy);
                r += c.r * kernel[k];
                g += c.g * kernel[k];
                b += c.b * kernel[k];
            }
            dst.At(x, y) = Color(r, g, b);
        }
    }

    return dst;
}
