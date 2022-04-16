#include "temporalMedianFilter.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

TemporalMedianFilter::TemporalMedianFilter(unsigned int scan_length,
                                           unsigned int median_width) {
    if (median_width < 1) {
        throw invalid_argument("median_width can not be less than 1");
    }

    this->scan_length = scan_length;
    this->median_width = median_width;

    history.resize(scan_length);
    sorted.resize(scan_length);
}

void TemporalMedianFilter::update(std::vector<float> &scan) {
    if (scan.size() != scan_length) {
        throw invalid_argument("scan length of " + to_string(scan.size()) +
                               " does not match expected scan length of " +
                               to_string(scan_length));
    }

    for (int i = 0; i < scan.size(); i++) {
        // Insert the new value to the back of the queue
        history[i].push(scan[i]);

        // Insert the new value in the sorted vector
        auto it = lower_bound(sorted[i].begin(), sorted[i].end(), scan[i]);
        sorted[i].insert(it, scan[i]);

        // Remove the oldest value in our median window if we exceed the window
        // width
        if (history[i].size() > median_width) {
            // Erase the oldest value from the sorted vector
            it = lower_bound(sorted[i].begin(), sorted[i].end(),
                             history[i].front());
            sorted[i].erase(it);

            // Pop the oldest value from the queue
            history[i].pop();
        }

        // Update the provided scan array with the calculated median
        if (history[i].size() & 1)
            scan[i] = sorted[i][history[i].size() / 2];
        else
            scan[i] = (sorted[i][history[i].size() / 2] +
                       sorted[i][history[i].size() / 2 - 1]) *
                      0.5f;
    }
}