#pragma once

#include "Filter.h"
#include <queue>

class TemporalMedianFilter : Filter {
public:
    /** Initialize filter with specified limits
     *
     *  @param scan_length expected length of scans
     *  @param median_width number of previous scans to consider for filtration
     *  @return INVALID_PARAM if median_width is less than 1
     *          OK otherwise
     */
    Status init(unsigned int scan_length, unsigned int median_width);
    
    /** Implementation of base update() function
     * 
     *  @param scan newest scan, which is updated in-place with filtered values
     *  @return NOT_INITIALIZED if init() was not previously called, 
     *          INVALID_PARAM if scan length does not match expected length
     *          OK otherwise
     */
    Status update(std::vector<float> &scan);

private:
    std::vector<std::queue<float>> temporal_sort;
    std::vector<std::vector<float>> magnitude_sort;

    unsigned int scan_length;
    unsigned int median_width;
};