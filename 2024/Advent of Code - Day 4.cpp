#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include "utils.cpp"

bool in_grid(int x, int y, int width, int height);

int main() {
    std::vector<std::string> lines = read_lines("Advent of Code - Day 4.txt");
    int sum = 0;
    // Part 1
    for (int row = 0; row < lines.size(); row++) {
        for (int col = 0; col < lines[row].size(); col++) {
            // Look for "XMAS" in all directions from all directions
            if (in_grid(col + 3, row, lines[row].size(), lines.size())) {
                if (lines[row][col] == 'X' && lines[row][col + 1] == 'M' && lines[row][col + 2] == 'A' && lines[row][col + 3] == 'S') {
                    sum++;
                }
            }
            if (in_grid(col, row + 3, lines[row].size(), lines.size())) {
                if (lines[row][col] == 'X' && lines[row + 1][col] == 'M' && lines[row + 2][col] == 'A' && lines[row + 3][col] == 'S') {
                    sum++;
                }
            }
            if (in_grid(col - 3, row, lines[row].size(), lines.size())) {
                if (lines[row][col] == 'X' && lines[row][col - 1] == 'M' && lines[row][col - 2] == 'A' && lines[row][col - 3] == 'S') {
                    sum++;
                }
            }
            if (in_grid(col, row - 3, lines[row].size(), lines.size())) {
                if (lines[row][col] == 'X' && lines[row - 1][col] == 'M' && lines[row - 2][col] == 'A' && lines[row - 3][col] == 'S') {
                    sum++;
                }
            }
            if (in_grid(col + 3, row + 3, lines[row].size(), lines.size())) {
                if (lines[row][col] == 'X' && lines[row + 1][col + 1] == 'M' && lines[row + 2][col + 2] == 'A' && lines[row + 3][col + 3] == 'S') {
                    sum++;
                }
            }
            if (in_grid(col - 3, row + 3, lines[row].size(), lines.size())) {
                if (lines[row][col] == 'X' && lines[row + 1][col - 1] == 'M' && lines[row + 2][col - 2] == 'A' && lines[row + 3][col - 3] == 'S') {
                    sum++;
                }
            }
            if (in_grid(col + 3, row - 3, lines[row].size(), lines.size())) {
                if (lines[row][col] == 'X' && lines[row - 1][col + 1] == 'M' && lines[row - 2][col + 2] == 'A' && lines[row - 3][col + 3] == 'S') {
                    sum++;
                }
            }
            if (in_grid(col - 3, row - 3, lines[row].size(), lines.size())) {
                if (lines[row][col] == 'X' && lines[row - 1][col - 1] == 'M' && lines[row - 2][col - 2] == 'A' && lines[row - 3][col - 3] == 'S') {
                    sum++;
                }
            }
            
        }
    }
    std::cout << sum << std::endl;

    // Part 2
    sum = 0;
    // Looking for MAS in the shape of an X
    for (int row = 1; row < lines.size() - 1; row++) {
        for (int col = 1; col < lines[row].size() - 1; col++) {
            // Centre on A and look for M and S in the shape of an X
            if (lines[row][col] == 'A') {
                int current_sum = 0;
                if (lines[row - 1][col - 1] == 'M' && lines[row + 1][col + 1] == 'S') {
                    current_sum++;
                    // std::cout << "row " << row << " col " << col << std::endl;
                }
                if (lines[row - 1][col + 1] == 'M' && lines[row + 1][col - 1] == 'S') {
                    current_sum++;
                    // std::cout << "row " << row << " col " << col << std::endl;
                }
                if (lines[row + 1][col - 1] == 'M' && lines[row - 1][col + 1] == 'S') {
                    current_sum++;
                    // std::cout << "row " << row << " col " << col << std::endl;
                }
                if (lines[row + 1][col + 1] == 'M' && lines[row - 1][col - 1] == 'S') {
                    current_sum++;
                    // std::cout << "row " << row << " col " << col << std::endl;
                }
                if (current_sum == 2) {
                    sum++;
                }
            }
        }
    }
    std::cout << sum << std::endl;
} 

bool in_grid(int x, int y, int width, int height) {
    return x >= 0 && x < width && y >= 0 && y < height;
}