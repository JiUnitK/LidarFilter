#include <gtest/gtest.h>
#include "RangeFilter.h"

using namespace std;

TEST(RangeFilter, Init_ValidParam)
{
    RangeFilter filter;

    vector<float> test_scan{1, 2, 3, 4, 5, 6};
    const float MIN = 2.0f;
    const float MAX = 4.5f;

    Filter::Status status = filter.init(MIN, MAX);

    EXPECT_EQ(Filter::Status::OK, status);
}

TEST(RangeFilter, Init_InvalidParam)
{
    RangeFilter filter;

    vector<float> test_scan{1, 2, 3, 4, 5, 6};
    const float MIN = 7.0f;
    const float MAX = 4.5f;

    Filter::Status status = filter.init(MIN, MAX);

    EXPECT_EQ(Filter::Status::INVALID_PARAM, status);
}

TEST(RangeFilter, Update_WithoutInit) {
    RangeFilter filter;

    vector<float> test_scan{1, 2, 3, 4, 5, 6};
    Filter::Status status = filter.update(test_scan);

    EXPECT_EQ(Filter::Status::NOT_INITIALIZED, status);
}

TEST(RangeFilter, Update) {
    RangeFilter filter;

    vector<float> test_scan{1, 2, 3, 4, 5, 6};
    vector<float> expected_scan{1, 2, 3, 4, 4.5, 4.5};
    const float MIN = 1.0f;
    const float MAX = 4.5f;

    Filter::Status init_status = filter.init(MIN, MAX);
    Filter::Status update_status = filter.update(test_scan);

    EXPECT_EQ(Filter::Status::OK, init_status);
    EXPECT_EQ(Filter::Status::OK, update_status);
    EXPECT_EQ(test_scan, expected_scan);
}

TEST(RangeFilter, Reinitialize) {
    RangeFilter filter;

    vector<float> test_scan{1, 2, 3, 4, 5, 6};
    const float MIN = 1.0f;
    const float MAX = 4.5f;

    Filter::Status init_status = filter.init(MIN, MAX);
    Filter::Status update_status = filter.update(test_scan);

    // Modify test_scan to their original values
    test_scan = {1, 2, 3, 4, 5, 6};
    vector<float> expected_scan = {3.2, 3.2, 3.2, 4, 4.5, 4.5};

    init_status = filter.init(3.2f, MAX);
    update_status = filter.update(test_scan);

    EXPECT_EQ(Filter::Status::OK, init_status);
    EXPECT_EQ(Filter::Status::OK, update_status);
    EXPECT_EQ(test_scan, expected_scan);
}