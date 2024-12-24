#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.cpp"

int main() {
    std::vector<std::string> lines = read_lines("Advent of Code - Day 2.txt");
    // find the string mul(XX,XX) 
    int sum = 0;
    for (std::string line : lines) {
        for (int i = 0; i < line.size(); i++) {
            int num1 = 0;
            int num2 = 0;
            // find mul first
            if (line[i] == 'm' && line[i + 1] == 'u' && line[i + 2] == 'l') {
                // find the first parenthesis
                int first_parenthesis = i + 4;
                if (line[first_parenthesis] != '(') {
                    continue;
                } e
                // find the second parenthesis
                int second_parenthesis = line.find(')', first_parenthesis);
                // check that there are numbers separated by a comma
                for (int j = first_parenthesis + 1; j < second_parenthesis; j++) {
                    if (line[j] == ',') {
                        num1 = std::stoi(line.substr(first_parenthesis + 1, j - first_parenthesis - 1));
                        num2 = std::stoi(line.substr(j + 1, second_parenthesis - j - 1));
                        break;
                    }
                }
            }
            sum += num1 * num2;
        }
    }
    std::cout << sum << std::endl;
} 
