// Tree.cpp
//
// Very basic binary tree implementation for the native two sum implementation
//
// HS 30.1.25

// TODO: rebalance tree

#include "Tree.h"

Tree::Tree(int ind, int val) :
    index(ind),
    value(val),
    left(std::unique_ptr<Tree>()),
    right(std::unique_ptr<Tree>()) {

}

Tree::~Tree() {
    // Nothing explicit to do - unique_ptrs go out of scope on their own
}


void Tree::insert(const int new_index, const int new_value) {
    if (new_value == value) {
        return;
    }
    
    // Can't spot simple way to drop code duplication due to left and right
    // not being interchangeable in this class definition
    // If used std::pair or std::array<2> and indexed instead maybe but this 3 line comment
    // already exceeds the space that would save in this function
    if (new_value > value) {
        if (right == nullptr) {
            right = std::make_unique<Tree>(new_index, new_value);
        } else {
            right->insert(new_index, new_value);
        }
    } else {
        if (left == nullptr) {
            left = std::make_unique<Tree>(new_index, new_value);
        } else {
            left->insert(new_index, new_value);
        }
    }

    // Rebalance
}

const int Tree::get_val() const {
    return value;
}

const int Tree::find_val(const int val) const {
    if (val == value) {
        return index;
    }
    if (val > value) {
        return right == nullptr ? right->find_val(val) : -1;
    } 
    return left == nullptr ? left->find_val(val) : -1;        
}
