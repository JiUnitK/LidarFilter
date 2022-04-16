#pragma once

#include "Filter.h"

class RangeFilter : public Filter {
public:
    /** Initialize filter with specified limits
     *
     *  @return INVALID_PARAM if range_min is greater than range_max. 
     *          OK otherwise
     */
    Status init(float range_min, float range_max);

    /** Implementation of base update() function
     * 
     *  @param scan newest scan, which is updated in-place with filtered values
     *  @return NOT_INITIALIZED if init() was not previously called, 
     *          OK otherwise
     */
    Status update(std::vector<float> &scan);

private:
    float range_min;
    float range_max;
};