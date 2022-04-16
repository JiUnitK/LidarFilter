#include "Filter.h"
#include "RangeFilter.h"
#include "TemporalMedianFilter.h"
#include <gtest/gtest.h>

using namespace std;

TEST(Filter, IsInit)
{
    Filter* filter;
    RangeFilter range_filter;
    filter = &range_filter;

    const float MIN = 1.0f;
    const float MAX = 4.5f;

    EXPECT_EQ(filter->isInit(), false);
    range_filter.init(MIN, MAX);
    EXPECT_EQ(filter->isInit(), true);
}

TEST(Filter, Update_RangeFilter)
{
    Filter* filter;
    RangeFilter range_filter;
    filter = &range_filter;

    const float MIN = 1.0f;
    const float MAX = 4.5f;
    range_filter.init(MIN, MAX);

    vector<float> test_scan{1, 2, 3, 4, 5, 6};
    vector<float> expected_scan{1, 2, 3, 4, 4.5, 4.5};

    filter->update(test_scan);
    EXPECT_EQ(test_scan, expected_scan);
}

TEST(Filter, Update_TemporalMedianFilter)
{
    Filter* filter;
    TemporalMedianFilter med_filter;
    filter = &med_filter;

    const float SCAN_LEN = 5;
    const float MEDIAN_WIDTH = 4;
    Filter::Status init_status = med_filter.init(SCAN_LEN, MEDIAN_WIDTH);

    vector<vector<float>> test_scans{
        {0, 1, 2, 1, 3},
        {1, 5, 7, 1, 3},
        {2, 3, 4, 1, 0},
        {3, 3, 3, 1, 3},
        {10, 2, 4, 0, 0}
    };

    vector<vector<float>> expected_scans{
        {0, 1, 2, 1, 3},
        {0.5, 3, 4.5, 1, 3},
        {1, 3, 4, 1, 3},
        {1.5, 3, 3.5, 1, 3},
        {2.5, 3, 4, 1, 1.5}
    };

    EXPECT_EQ(Filter::Status::OK, init_status);
    for (int i=0; i<test_scans.size(); i++)
    {
        Filter::Status update_status = filter->update(test_scans[i]);
        EXPECT_EQ(Filter::Status::OK, update_status);
        EXPECT_EQ(test_scans[i], expected_scans[i]);
    }
}