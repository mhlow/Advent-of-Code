#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.cpp"
#include <regex>

int main() {
    std::vector<std::string> lines = read_lines("Advent of Code - Day 3.txt");
    // find the string mul(XX,XX) 
    int sum = 0;
    std::regex re("mul\\((\\d+),(\\d+)\\)");
    for (std::string line : lines) {
        std::smatch match;
        std::string::const_iterator searchStart( line.cbegin() );
        while ( regex_search( searchStart, line.cend(), match, re ) ) {
            sum += std::stoi(match[1]) * std::stoi(match[2]);
            searchStart = match.suffix().first;
        }
    }
    std::cout << sum << std::endl;

    // Part 2
    // Find the most recent "do" or "don't" and apply that to future "mul"
    sum = 0;
    bool is_do = true;
    std::regex regex_do("(do\\(\\)|don't\\(\\)|mul\\(\\d+,\\d+\\))");
    for (std::string line : lines) {
        std::smatch match;
        std::string::const_iterator searchStart( line.cbegin() );
        while ( regex_search( searchStart, line.cend(), match, regex_do ) ) {
            if (match[0] == "do()") {
                std::cout << "do" << std::endl;
                is_do = true;
            } else if (match[0] == "don't()") {
                std::cout << "don't" << std::endl;
                is_do = false;
            } else {
                if (is_do) {
                    regex_search( searchStart, line.cend(), match, re );
                    sum += std::stoi(match[1]) * std::stoi(match[2]);
                }
            }
            searchStart = match.suffix().first;
        }
    }
    std::cout << sum << std::endl;
} 
