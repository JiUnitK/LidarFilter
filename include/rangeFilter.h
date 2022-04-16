#include <vector>

class RangeFilter {
public:
    RangeFilter(float range_min, float range_max);

    void update(std::vector<float> &scan);

private:
    float range_min;
    float range_max;
};