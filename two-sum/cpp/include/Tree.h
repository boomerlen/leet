// Tree.h
//
// Binary tree thingo
//
// U get the idea
// HS 29.1.25

#pragma once 

#include <memory>

class Tree {
public:
    Tree(int ind, int val);
    ~Tree();

    void insert(const int new_index, const int new_value);

    const int get_val() const;
    
    // Returns index of desired value as stored by tree or -1 if not found
    const int find_val(const int val) const;
private:
    // Parent owns child trees
    std::unique_ptr<Tree> left;
    std::unique_ptr<Tree> right;

    int index, value;
};
