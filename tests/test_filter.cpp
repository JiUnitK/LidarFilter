#include <gtest/gtest.h>
#include "rangeFilter.h"
#include "temporalMedianFilter.h"

// Demonstrate some basic assertions.
TEST(TestFilter, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect equality.
  EXPECT_EQ(7 * 6, 42);

  RangeFilter range_filter(0.5, 1.5);
}
