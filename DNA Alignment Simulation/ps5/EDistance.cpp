// Copyright 2024 <Thomas Boyajian>
#include "EDistance.hpp"
#include <stdexcept>
#include <algorithm>

EDistance::EDistance(const std::string& s1, const std::string& s2)
    : str1(s1), str2(s2), calculated(false) {
    if (s1.empty() || s2.empty()) {
        throw std::invalid_argument("Input strings cannot be empty");
    }
    initializeMatrix();
}

EDistance::~EDistance() {
    // Vector will clean up automatically
}

int EDistance::penalty(char a, char b) {
    return (a == b) ? 0 : 1;
}

int EDistance::min3(int a, int b, int c) {
    return std::min(std::min(a, b), c);
}

void EDistance::initializeMatrix() {
    // Initialize matrix with dimensions (str1.length() + 1) x (str2.length() + 1)
    opt.resize(str1.length() + 1, std::vector<int>(str2.length() + 1));

    // Initialize last row and column
    for (size_t i = 0; i <= str1.length(); ++i) {
        opt[i][str2.length()] = 2 * (str1.length() - i);
    }
    for (size_t j = 0; j <= str2.length(); ++j) {
        opt[str1.length()][j] = 2 * (str2.length() - j);
    }
}

void EDistance::fillMatrix() {
    if (calculated) return;

    // Fill matrix from bottom-right to top-left
    for (int i = str1.length() - 1; i >= 0; --i) {
        for (int j = str2.length() - 1; j >= 0; --j) {
            // Calculate the three possible moves
            int match = opt[i + 1][j + 1] + penalty(str1[i], str2[j]);
            int gapInStr1 = opt[i][j + 1] + 2;  // Gap in first string
            int gapInStr2 = opt[i + 1][j] + 2;  // Gap in second string

            // Take the minimum of the three options
            opt[i][j] = min3(match, gapInStr1, gapInStr2);
        }
    }

    calculated = true;
}

int EDistance::optDistance() {
    fillMatrix();
    return opt[0][0];
}

std::string EDistance::alignment() {
    if (!calculated) {
        fillMatrix();
    }

    std::string result;
    size_t i = 0, j = 0;

    while (i < str1.length() || j < str2.length()) {
        if (i == str1.length()) {
            // Must take gap in first string
            result += "-";
            result += " ";
            result += str2[j];
            result += " ";
            result += "2\n";
            j++;
        } else if (j == str2.length()) {
            // Must take gap in second string
            result += str1[i];
            result += " ";
            result += "-";
            result += " ";
            result += "2\n";
            i++;
        } else {
            int match = opt[i + 1][j + 1] + penalty(str1[i], str2[j]);

            if (opt[i][j] == match) {
                // Characters are aligned
                result += str1[i];
                result += " ";
                result += str2[j];
                result += " ";
                result += std::to_string(penalty(str1[i], str2[j]));
                result += "\n";
                i++;
                j++;
            } else if (opt[i][j] == opt[i + 1][j] + 2) {
                // Gap in second string
                result += str1[i];
                result += " ";
                result += "-";
                result += " ";
                result += "2\n";
                i++;
            } else {
                // Gap in first string
                result += "-";
                result += " ";
                result += str2[j];
                result += " ";
                result += "2\n";
                j++;
            }
        }
    }

    return result;
}
