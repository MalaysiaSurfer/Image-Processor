#include "edgedetection_filter.h"
#include "grayscale_filter.h"

Image EdgeDetectionFilter::Apply(const Image& src) const {
    GrayscaleFilter gs;
    Image gray = gs.Apply(src);
    Image dst(gray.GetWidth(), gray.GetHeight());
    static const int Kernel[3][3] = {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}};
    for (size_t y = 0; y < gray.GetHeight(); ++y) {
        for (size_t x = 0; x < gray.GetWidth(); ++x) {
            double sum_p = 0.0;
            for (int neigh_y = -1; neigh_y < 2; ++neigh_y) {
                for (int neigh_x = -1; neigh_x < 2; ++neigh_x) {
                    const Color& c = gray.SafeAt(static_cast<int>(x) + neigh_x, static_cast<int>(y) + neigh_y);
                    double multiplier = static_cast<double>(Kernel[neigh_y + 1][neigh_x + 1]);
                    sum_p += c.r * multiplier;
                }
            }
            double val = 0.0;
            if (sum_p > threshold_) {
                val = 1.0;
            }
            dst.At(x, y) = Color(val, val, val);
        }
    }
    return dst;
}
