#include <gtest/gtest.h>
#include "RangeFilter.h"

using namespace std;

TEST(RangeFilter, NotInit) {
    RangeFilter range_filter;

    vector<float> test_scan{1, 2, 3, 4, 5, 6};
    Filter::Status status = range_filter.update(test_scan);

    EXPECT_EQ(Filter::Status::NOT_INITIALIZED, status);
}