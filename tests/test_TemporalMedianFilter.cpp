#include <gtest/gtest.h>
#include "TemporalMedianFilter.h"

using namespace std;

TEST(TemporalMedianFilter, Init_InvalidParam)
{
    TemporalMedianFilter filter;
    const float SCAN_LEN = 5;
    const float MEDIAN_WIDTH = 0;

    Filter::Status status = filter.init(SCAN_LEN, MEDIAN_WIDTH);

    EXPECT_EQ(Filter::Status::INVALID_PARAM, status);
}

TEST(TemporalMedianFilter, Init_ValidParam)
{
    TemporalMedianFilter filter;
    const float SCAN_LEN = 5;
    const float MEDIAN_WIDTH = 4;

    Filter::Status status = filter.init(SCAN_LEN, MEDIAN_WIDTH);

    EXPECT_EQ(Filter::Status::OK, status);
}

TEST(TemporalMedianFilter, Update_InvalidScanLength)
{
    TemporalMedianFilter filter;
    const float SCAN_LEN = 5;
    const float MEDIAN_WIDTH = 4;

    Filter::Status init_status = filter.init(SCAN_LEN, MEDIAN_WIDTH);

    vector<float> test_scan{1, 2, 3, 4, 5, 6};
    Filter::Status update_status = filter.update(test_scan);

    EXPECT_EQ(Filter::Status::OK, init_status);
    EXPECT_EQ(Filter::Status::INVALID_PARAM, update_status);
}

TEST(TemporalMedianFilter, Update)
{
    TemporalMedianFilter filter;
    const float SCAN_LEN = 5;
    const float MEDIAN_WIDTH = 4;

    Filter::Status init_status = filter.init(SCAN_LEN, MEDIAN_WIDTH);

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
        Filter::Status update_status = filter.update(test_scans[i]);
        EXPECT_EQ(Filter::Status::OK, update_status);
        EXPECT_EQ(test_scans[i], expected_scans[i]);
    }
}