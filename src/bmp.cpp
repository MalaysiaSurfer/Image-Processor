#include "bmp.h"

#include <stdexcept>
#include <fstream>
#include <cstdint>
#include <vector>

#pragma pack(push, 1)
struct BMPFileHeader {
    uint16_t SIGNATURE;
    uint32_t file_size;
    uint16_t reserved1;
    uint16_t reserved2;
    uint32_t data_offset;
};

struct BMPInfoHeader {
    uint32_t header_size;
    int32_t width;
    int32_t height;
    uint16_t planes;
    uint16_t BITS_PER_PIXEL;
    uint32_t compression;
    uint32_t image_size;
    int32_t x_pixels_per_meter;
    int32_t y_pixels_per_meter;
    uint32_t colors_used;
    uint32_t colors_important;
};
#pragma pack(pop)

const int SIGNATURE = 0x4D42;
const int BITS_PER_PIXEL = 24;
const double RGB = 255.0;
const double FAST_ROUND = 0.5;

Image LoadBMP(const std::string& path) {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + path);
    }

    BMPFileHeader file_header{};
    file.read(reinterpret_cast<char*>(&file_header), sizeof(file_header));
    if (!file) {
        throw std::runtime_error("Failed to read file header");
    }
    if (file_header.SIGNATURE != SIGNATURE) {
        throw std::runtime_error("Not a BMP file: " + path);
    }

    BMPInfoHeader info_header{};
    file.read(reinterpret_cast<char*>(&info_header), sizeof(info_header));
    if (!file) {
        throw std::runtime_error("Failed to read info header");
    }
    if (info_header.BITS_PER_PIXEL != BITS_PER_PIXEL) {
        throw std::runtime_error("Only 24-bit BMP supported");
    }
    if (info_header.compression != 0) {
        throw std::runtime_error("Compressed BMP not supported");
    }

    int32_t width = info_header.width;
    int32_t height = info_header.height;
    Image image(static_cast<size_t>(width), static_cast<size_t>(height));

    file.seekg(file_header.data_offset, std::ios::beg);

    size_t row_size = (width * 3 + 3) & ~3u;
    std::vector<uint8_t> row_buf(row_size);

    for (int32_t row = 0; row < height; ++row) {
        file.read(reinterpret_cast<char*>(row_buf.data()), static_cast<std::streamsize>(row_size));
        if (!file) {
            throw std::runtime_error("Unexpected end of BMP data");
        }

        int32_t y = height - 1 - row;
        for (int32_t x = 0; x < width; ++x) {
            uint8_t blue = row_buf[x * 3 + 0];
            uint8_t green = row_buf[x * 3 + 1];
            uint8_t red = row_buf[x * 3 + 2];
            image.At(static_cast<size_t>(x), static_cast<size_t>(y)) = Color(red / RGB, green / RGB, blue / RGB);
        }
    }

    return image;
}

void SaveBMP(const Image& image, const std::string& path) {
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot write to file: " + path);
    }

    int32_t width = static_cast<int32_t>(image.GetWidth());
    int32_t height = static_cast<int32_t>(image.GetHeight());
    size_t row_size = (static_cast<size_t>(width) * 3 + 3) & ~3u;
    uint32_t data_size = static_cast<uint32_t>(row_size * static_cast<size_t>(height));

    BMPFileHeader file_header{};
    file_header.SIGNATURE = SIGNATURE;
    file_header.file_size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + data_size;
    file_header.reserved1 = 0;
    file_header.reserved2 = 0;
    file_header.data_offset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader);

    BMPInfoHeader info_header{};
    info_header.header_size = sizeof(info_header);
    info_header.width = width;
    info_header.height = height;
    info_header.planes = 1;
    info_header.BITS_PER_PIXEL = BITS_PER_PIXEL;
    info_header.compression = 0;
    info_header.image_size = 0;
    info_header.x_pixels_per_meter = 0;
    info_header.y_pixels_per_meter = 0;
    info_header.colors_used = 0;
    info_header.colors_important = 0;

    file.write(reinterpret_cast<const char*>(&file_header), sizeof(file_header));
    file.write(reinterpret_cast<const char*>(&info_header), sizeof(info_header));

    std::vector<uint8_t> row_buf(row_size, 0);

    for (int32_t row = 0; row < height; ++row) {
        int32_t y = height - 1 - row;
        for (int32_t x = 0; x < width; ++x) {
            Color c = image.At(static_cast<size_t>(x), static_cast<size_t>(y));
            row_buf[x * 3 + 0] = static_cast<uint8_t>(c.b * RGB + FAST_ROUND);
            row_buf[x * 3 + 1] = static_cast<uint8_t>(c.g * RGB + FAST_ROUND);
            row_buf[x * 3 + 2] = static_cast<uint8_t>(c.r * RGB + FAST_ROUND);
        }
        file.write(reinterpret_cast<const char*>(row_buf.data()), static_cast<std::streamsize>(row_size));
    }
}
