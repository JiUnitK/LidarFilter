#include <queue>
#include <vector>

class TemporalMedianFilter {
public:
    TemporalMedianFilter(unsigned int scan_length, unsigned int median_width);

    void update(std::vector<float> &scan);

private:
    std::vector<std::queue<float>> history;
    std::vector<std::vector<float>> sorted;

    unsigned int scan_length;
    unsigned int median_width;
};