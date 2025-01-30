// TwoSumNative.cpp
//
// Implementation of typical twosum solution using Btrees etc
//
// HS 29.1.25

#include "Solution.h"
#include "Tree.h"

#include <utility>
#include <vector>
#include <ranges>

// Why are these classes?
// It's happened now but this could very easily be encapsulation or
// whatever that design pattern is called where we just have a solution function
// that is overwritten depending on compilation arguments honestly wouldn't be that crazy
// In fact actually super simple - would just have the implementations provided in two files
// and only compile + link whichever is to be used.

TwoSumNative::TwoSumNative() {

}

TwoSumNative::~TwoSumNative() {

}

std::pair<int, int> TwoSumNative::run(const std::vector<int> &nums, int target) {
    // Pretty much a port of the rust solution
    if (nums.size() < 2) {
        throw std::out_of_range("nums is too short");
    }
    Tree tree(0, nums[0]);

    for (auto const [i, x] : std::views::enumerate(nums)) {
        int diff = target - x;
        int attempt = tree.find_val(diff);

        if (attempt != -1) {
            return std::pair<int, int>(i, attempt);
        }
        tree.insert(i, x);
    }
    
    return std::pair<int, int>(-1, -1);
}
