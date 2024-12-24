#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.cpp"

int is_rising(std::vector<int> level);
int is_falling(std::vector<int> level);

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


        // std::cout << safe << std::endl;
        sum += safe;
    }

    std::cout << "Part 1: " << sum << std::endl;

    // PART 2
    sum = 0;
    for (std::vector<int> level : levels) {
        // Remove one of the numbers one by one

        for (int i = 0; i < level.size(); i++) {
            std::vector<int> new_level(level.begin(), level.end());
            new_level.erase(new_level.begin() + i);

            if (is_rising(new_level) == 0 || is_falling(new_level) == 0) {
                sum++;
                break;
            }
        }

        // for (int i = 0; i < level.size() - 1; i++) {
        //     std::cout << level[i] << " ";
        // }

        // std::cout << " || Rising: " <<  is_rising(level) << " || " << "Falling: " << is_falling(level) << std::endl;
    }

    std::cout << "Part 2: " << sum << std::endl;
}

int is_rising(std::vector<int> level) {
    if (level.size() == 2) {
        if (level[1] - level[0] > 0 && level[1] - level[0] <= 3) {
            return 0;
        }
        return 1;
    }
    if (level[1] - level[0] > 0 && level[1] - level[0] <= 3) {
        return is_rising(std::vector<int>(level.begin() + 1, level.end()));
    }
    return 1 + is_rising(std::vector<int>(level.begin() + 1, level.end()));
}


// Returns the number of mistakes
int is_falling(std::vector<int> level) {
    if (level.size() == 2) {
        if (level[0] - level[1] > 0 && level[0] - level[1] <= 3) {
            return 0;
        }
        return 1;
    }
    if (level[0] - level[1] > 0 && level[0] - level[1] <= 3) {
        return is_falling(std::vector<int>(level.begin() + 1, level.end()));
    }
    return 1 + is_falling(std::vector<int>(level.begin() + 1, level.end()));
}