#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.cpp"

int main() {
    std::vector<std::string> lines = read_lines("Advent of Code - Day 1.txt");
    int sum = 0;
    std::vector<int> left;
    std::vector<int> right;
    for (std::string line : lines) {
        std::vector<std::string> parts = split(line, ' ');
        left.push_back(std::stoi(parts[0]));
        right.push_back(std::stoi(parts[parts.size() - 1]));
    }

    // PART 1
    sum = 0;
    std::sort(left.begin(), left.end());
    std::sort(right.begin(), right.end());

    for (int i = 0; i < left.size(); i++) {
        sum += std::abs(left[i] - right[i]);
    }

    std::cout << "Part 1: " << sum << std::endl;

    // PART 2
    sum = 0;
    for (int leftnum : left) {
        int total = 0;
        for (int rightnum : right) {
            if (leftnum == rightnum) {
                total++;
            }
        }
        sum += total * leftnum;
    }

    std::cout << "Part 2: " << sum << std::endl;
    return 0;
}
