// main.cpp
// 
// Two-sum C++ implementation from more bsaic starting point
//
// HS, 27.1.25

#include <iostream>
#include <fstream>
#include <vector>

// Preprocessor inherits ideally from CMakeLists.txt

#ifdef MODE_TIMED
#include <chrono>
#include <vector>
#endif

#ifndef CSV_BUFLEN
#define CSV_BUFLEN 256
#endif

#include "Solution.h"

#define PAIR_CMP(x, y) ((x.first == y.first && x.second == y.second) || (x.second == y.first && x.first == y.second))

int main(int argc, char **argv) {
    
    // Assume test cases provided in csv given
    if (argc != 2) {
        std::cout << "Please provide one argument with the input test files" << std::endl;
        return -1;
    }
    
#ifdef RUNNER_GPU
    TwoSumAccelerated runner; 
#else
    TwoSumNative runner;
#endif
    
    // VERY simple csv parsing
    // Delimit array entries with spaces, perform NO csv error handling, def bad code
    // but not the point here
    auto file = std::ifstream(argv[1]);
    
    // Perform tests
    char buffer[CSV_BUFLEN];
    while (file.getline(buffer, CSV_BUFLEN)) {
        std::vector<int> nums;

        // Assume csv is not malformed
        // c string operations because I'm lazy and uncool
        int counter = 0;
        while (buffer[counter] != ',') {
            // Assume we have a number followed by space
            char num_buf[CSV_BUFLEN];

            int num_buf_counter = 0;
            while (buffer[counter] != ' ' && buffer[counter] != ',') {
                num_buf[num_buf_counter] = buffer[counter];
                counter++;
                num_buf_counter++;
            }
            num_buf[num_buf_counter] = '\0';
            nums.push_back(std::atoi(num_buf));
        }

        // Now target
        char num_buf[CSV_BUFLEN];

        int num_buf_counter = 0;
        while (buffer[counter] != ' ' && buffer[counter] != ',') {
            num_buf[num_buf_counter] = buffer[counter];
            counter++;
            num_buf_counter++;
        }
        num_buf[num_buf_counter] = '\0';
        int target = std::atoi(num_buf);\

        // Now pair of indices again space separated
        std::vector<int> indices_correct;
        while (buffer[counter] != '\n') {
            // Assume we have a number followed by space
            char num_buf[CSV_BUFLEN];

            int num_buf_counter = 0;
            while (buffer[counter] != ' ' && buffer[counter] != ',') {
                num_buf[num_buf_counter] = buffer[counter];
                counter++;
                num_buf_counter++;
            }
            num_buf[num_buf_counter] = '\0';
            indices_correct.push_back(std::atoi(num_buf));
        }

        if (indices_correct.size() != 2) {
            // Parsing error
            throw std::runtime_error("Tests file parsing error\n");
        }
        std::pair<int, int> pair_correct = std::make_pair(indices_correct[0], indices_correct[1]);

        // Situation changes based on whether we record timing information or not
        // Timed mode does not confirm correctness, just times algorithm execution
#ifdef MODE_TIMED
        const auto time_start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < MODE_TIMED_N, i++) {
            runner.run(nums, target);
        }
        const auto time_end = std::chrono::high_resolution_clock::now();
        const std::chrono::duration<double, std::micro> dur = time_end - time_start;

        std::cout << "N nums: " << nums.size() << ", Time taken: " << dur << std::endl;
#else
        std::pair<int, int> result = runner.run(nums, target);
        const bool correct = PAIR_CMP(result, pair_correct);
        
        std::cout << "Nums: ";
        for (const auto &val : nums) std::cout << val;

        std::cout << "Target: " << target << ", Correct: " << correct << std::endl;
#endif
    }
}
