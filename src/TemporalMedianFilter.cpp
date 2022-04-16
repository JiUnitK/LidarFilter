#include "TemporalMedianFilter.h"
#include <algorithm>
#include <stdexcept>

using namespace std;
using TMF = TemporalMedianFilter;

Filter::Status TMF::init(unsigned int scan_length, unsigned int median_width) {
    if (median_width < 1) {
        return Filter::Status::INVALID_PARAM;
    }

    this->scan_length = scan_length;
    this->median_width = median_width;

    temporal_sort.clear();
    magnitude_sort.clear();

    temporal_sort.resize(scan_length);
    magnitude_sort.resize(scan_length);

    is_init = true;

    return Filter::Status::OK;
}

Filter::Status TMF::update(std::vector<float> &scan) {
    if (!is_init)
        return Filter::Status::NOT_INITIALIZED;

    if (scan.size() != scan_length)
        return Filter::Status::INVALID_PARAM;

    for (int i = 0; i < scan.size(); i++) {
        // In temporal order, we always push a new scan to the back of the queue
        temporal_sort[i].push(scan[i]);

        // Insert the new value by magnitude
        auto it = lower_bound(magnitude_sort[i].begin(), magnitude_sort[i].end(), scan[i]);
        magnitude_sort[i].insert(it, scan[i]);

        // Remove oldest value in our median window if needed
        if (temporal_sort[i].size() > median_width) {
            // Erase the oldest value from the magnitude_sort vector
            it = lower_bound(magnitude_sort[i].begin(), magnitude_sort[i].end(),
                             temporal_sort[i].front());
            magnitude_sort[i].erase(it);

            // Pop the oldest value from the queue
            temporal_sort[i].pop();
        }

        // Update the provided scan array with the calculated median
        if (temporal_sort[i].size() & 1)
        {
            // For odd numbered windows, simple take the middle value
            scan[i] = magnitude_sort[i][temporal_sort[i].size() / 2];
        }
        else {
            // For even numbered windows, we take the average of the two middle
            // values
            scan[i] = (magnitude_sort[i][temporal_sort[i].size() / 2] +
                       magnitude_sort[i][temporal_sort[i].size() / 2 - 1]) *
                      0.5f;
        }
    }

    return Filter::Status::OK;
}