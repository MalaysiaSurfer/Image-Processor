#include "twirl_filter.h"

#include <cmath>

Image TwirlFilter::Apply(const Image& src) const {
    Image dst(src.GetWidth(), src.GetHeight());

    double cx = src.GetWidth() / 2.0;
    double cy = src.GetHeight() / 2.0;
    for (size_t y = 0; y < src.GetHeight(); ++y) {
        for (size_t x = 0; x < src.GetWidth(); ++x) {
            double dx = static_cast<double>(x) - cx;
            double dy = static_cast<double>(y) - cy;
            double r = std::sqrt(dx * dx + dy * dy);
            if (r < radius_) {
                double twist = angle_ * (1.0 - r / radius_);
                double theta = std::atan2(dy, dx) + twist;
                int src_x = static_cast<int>(cx + r * std::cos(theta));
                int src_y = static_cast<int>(cy + r * std::sin(theta));
                dst.At(x, y) = src.SafeAt(src_x, src_y);
            } else {
                dst.At(x, y) = src.At(x, y);
            }
        }
    }
    return dst;
}
