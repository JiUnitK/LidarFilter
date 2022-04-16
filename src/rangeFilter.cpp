#include "rangeFilter.h"
#include <stdexcept>

using namespace std;

RangeFilter::RangeFilter(float range_min, float range_max) {
    if (range_min > range_max) {
        throw invalid_argument("range_min (value " + to_string(range_min) +
                               ") must not be greater than range_max (value " +
                               to_string(range_max) + ")");
    }

    this->range_min = range_min;
    this->range_max = range_max;
}

void RangeFilter::update(std::vector<float> &scan) {
    for (auto &value : scan) {
        if (value > range_max)
            value = range_max;
        else if (value < range_min)
            value = range_min;
    }
}