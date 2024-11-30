// Copyright 2024 <Thomas Boyajian>
#pragma once

#include <string>
#include <vector>

class EDistance {
 public:
    // Constructor that takes two strings to compare
    EDistance(const std::string& s1, const std::string& s2);

    // Destructor to clean up any dynamic memory
    ~EDistance();

    // Returns penalty for aligning two characters (0 if match, 1 if mismatch)
    static int penalty(char a, char b);

    // Returns minimum of three integers
    static int min3(int a, int b, int c);

    // Calculates and returns the optimal edit distance
    int optDistance();

    // Returns a formatted string showing the alignment
    std::string alignment();

 private:
    std::string str1;    // First sequence
    std::string str2;    // Second sequence
    std::vector<std::vector<int>> opt;  // Dynamic programming matrix
    bool calculated;     // Flag to track if matrix has been calculated

    // Helper method to initialize the matrix
    void initializeMatrix();

    // Helper method to fill the matrix
    void fillMatrix();
};
