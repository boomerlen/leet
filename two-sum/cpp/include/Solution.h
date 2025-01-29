// Solution.h
// 
// Standard solution class
//
// HS 27.1.25

#pragma once

#include <utility>
#include <vector>

class TwoSumRunner {
public:
    inline TwoSumRunner() {}
    virtual ~TwoSumRunner() {}
    
    virtual std::pair<int, int> run(const std::vector<int> &nums, int target) = 0;
};

class TwoSumNative : public TwoSumRunner {
public:
    TwoSumNative();
    ~TwoSumNative();

    std::pair<int, int> run(const std::vector<int> &nums, int target);
};

class TwoSumAccelerated : public TwoSumRunner {
public:
    TwoSumAccelerated();
    ~TwoSumAccelerated();

    std::pair<int, int> run(const std::vector<int> &nums, int target);
};

