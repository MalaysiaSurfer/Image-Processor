#pragma once

#include "filter.h"

class SharpeningFilter : public Filter {
public:
    Image Apply(const Image& src) const override;
};
