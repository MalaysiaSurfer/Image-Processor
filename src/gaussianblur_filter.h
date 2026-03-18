#pragma once

#include "filter.h"

class GaussianBlurFilter : public Filter {
public:
    explicit GaussianBlurFilter(double sigma) : sigma_(sigma) {
    }
    Image Apply(const Image& src) const override;

private:
    double sigma_;
};
