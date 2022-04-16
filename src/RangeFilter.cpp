#include "RangeFilter.h"
#include <stdexcept>

using namespace std;
using RF = RangeFilter;

Filter::Status RF::init(float range_min, float range_max) {
    if (range_min > range_max) {
        return RF::Status::INVALID_PARAM;
    }

    this->range_min = range_min;
    this->range_max = range_max;

    is_init = true;
    return RF::Status::OK;
}

Filter::Status RF::update(std::vector<float> &scan) {
    if (!is_init)
        return Filter::Status::NOT_INITIALIZED;

    for (auto &point : scan) {
        point = min(point, range_max);
        point = max(point, range_min);
    }

    return RF::Status::OK;
}