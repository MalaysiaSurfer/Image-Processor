#pragma once

#include "filter.h"

class TwirlFilter : public Filter {
public:
    explicit TwirlFilter(double radius, double angle) : radius_(radius), angle_(angle) {
    }
    Image Apply(const Image& src) const override;

private:
    double radius_;
    double angle_;
};