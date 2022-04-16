#pragma once

#include <vector>

class Filter {
public:
    enum class Status { OK, NOT_INITIALIZED, INVALID_PARAM };

    /** Takes latest scan and performs in-place filtration
     *
     *  @param scan newest scan, which is updated in-place with filtered values
     *  @return Status value of filtration, which will vary depending on
     *          concrete implementation
     */
    virtual Status update(std::vector<float> &scan) = 0;

    /** Getter for initialization status
     */
    bool isInit() const { return is_init; };

protected:
    bool is_init = false;
};