#pragma once

#include "filter.h"

class EdgeDetectionFilter : public Filter {
public:
    explicit EdgeDetectionFilter(double threshold) : threshold_(threshold) {
    }
    Image Apply(const Image& src) const override;

private:
    double threshold_;
};