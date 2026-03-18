#pragma once

#include "image.h"

class Filter {
public:
    virtual ~Filter() = default;
    virtual Image Apply(const Image& src) const = 0;
};
