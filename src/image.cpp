#include "image.h"

#include <algorithm>

Image::Image(size_t width, size_t height) : width_(width), height_(height), pixels_(width * height) {
}

const Color& Image::SafeAt(int x, int y) const {
    int cx = std::clamp(x, 0, static_cast<int>(width_) - 1);
    int cy = std::clamp(y, 0, static_cast<int>(height_) - 1);
    return At(static_cast<size_t>(cx), static_cast<size_t>(cy));
}
