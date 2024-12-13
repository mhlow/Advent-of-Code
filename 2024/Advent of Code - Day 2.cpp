#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.cpp"

int main() {
    std::vector<std::string> lines = read_lines("Advent of Code - Day 2.txt");
    std::vector<std::vector<int>> levels;
    for (std::string line : lines) {
        std::vector<std::string> line_level = split(line, ' ');
        std::vector<int> dims;
        for (std::string level : line_level) {
            dims.push_back(std::stoi(level));
        }
        levels.push_back(dims);
    }

    // PART 1
    int sum = 0;
    for (std::vector<int> level : levels) {
        bool rising = false;
        bool safe = true;
        if (level[0] < level[1]) {
            rising = true;
        }
        if (level[0] == level[1]) {
            safe = false;
            continue;
        }

        if (rising) {
            for (int i = 1; i < level.size() - 1; i++) {
                if (level[i] > level[i + 1]) {
                    safe = false;
                    break;
                }
            }
        } else {
            for (int i = 1; i < level.size() - 1; i++) {
                if (level[i] < level[i + 1]) {
                    safe = false;
                    break;
                }
            }
        }

        for (int i = 0; i < level.size() - 1; i++) {
            if (abs(level[i] - level[i + 1]) > 3 || abs(level[i] - level[i + 1]) == 0) {
                safe = false;
                break;
            }
        }


        std::cout << safe << std::endl;
        sum += safe;
    }

    std::cout << "Part 1: " << sum << std::endl;

    // PART 2

}

