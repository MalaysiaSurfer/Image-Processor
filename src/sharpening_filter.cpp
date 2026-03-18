#include "sharpening_filter.h"

#include <vector>

Image SharpeningFilter::Apply(const Image& src) const {
    Image dst(src.GetWidth(), src.GetHeight());
    static const int KERNEL[3][3] = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
    for (size_t y = 0; y < src.GetHeight(); ++y) {
        for (size_t x = 0; x < src.GetWidth(); ++x) {
            double sum_r = 0.0;
            double sum_g = 0.0;
            double sum_b = 0.0;
            for (int neigh_y = -1; neigh_y < 2; ++neigh_y) {
                for (int neigh_x = -1; neigh_x < 2; ++neigh_x) {
                    const Color& c = src.SafeAt(static_cast<int>(x) + neigh_x, static_cast<int>(y) + neigh_y);
                    double multiplier = static_cast<double>(KERNEL[neigh_y + 1][neigh_x + 1]);
                    sum_r += c.r * multiplier;
                    sum_g += c.g * multiplier;
                    sum_b += c.b * multiplier;
                }
            }
            dst.At(x, y) = Color(sum_r, sum_g, sum_b).Clamp();
        }
    }
    return dst;
}
