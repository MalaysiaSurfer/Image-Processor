#pragma once

#include "color.h"
#include <vector>

class Image {
private:
    size_t width_;
    size_t height_;
    std::vector<Color> pixels_;

public:
    Image() = default;
    Image(size_t width, size_t height);
    size_t GetWidth() const {
        return width_;
    }
    size_t GetHeight() const {
        return height_;
    }
    Color& At(size_t x, size_t y) {
        return pixels_[y * width_ + x];
    }
    const Color& At(size_t x, size_t y) const {
        return pixels_[y * width_ + x];
    }
    const Color& SafeAt(int x, int y) const;
};