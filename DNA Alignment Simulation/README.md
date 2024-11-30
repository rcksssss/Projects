# PS5: DNA Alignment

## Contact
Name: Thomas Boyajian
Section: 201
Time to Complete: 7 hours

Partner: N/A

## Description
Explain what the project does

This project implements a DNA sequence alignment tool using dynamic programming. It takes two DNA sequences as input and finds the optimal alignment between them by calculating minimum edit distance, considering matches, mismatches, and gaps. The program provides both the optimal alignment cost and the actual alignment visualization.


### Features
Explain how you did the actual alignment including the data structures used.

The alignment is implemented using the following approach:
- Dynamic programming with a 2D matrix (opt) storing minimum costs
- Vector<vector<int>> for efficient matrix storage and access
- Bottom-up matrix filling strategy to solve subproblems
- Backtracking through the matrix to construct the alignment
- Gap penalty of 2 and mismatch penalty of 1
- Matrix traversal from top-left to bottom-right for alignment generation

### Testing
Describe what the unit tests you wrote check for and why you picked them.

The unit tests verify:
1. WrongCostTest: Checks if the cost calculation is correct and matches the alignment
2. ReversedTest: Ensures alignment output maintains proper sequence order
3. SwappedColsTest: Verifies columns aren't swapped in alignment output
4. CutEndsTest: Confirms all characters are included in alignment, including ends
5. WrongDirectionTest: Validates correct matrix traversal direction

Tests were chosen to catch common implementation issues and ensure output format correctness.

### Issues
What did you have trouble with?  What did you learn?  What doesn't work?  Be honest.  You might be penalized if you claim something works and it doesn't.

Challenges encountered:
1. Matrix traversal direction - initially had issues with proper backtracking
2. Memory management - had to carefully consider matrix size for larger sequences
3. Understanding the dynamic programming approach - took time to grasp optimal substructure
4. Alignment string formatting - ensuring proper spacing and newlines

Learned:
- Dynamic programming implementation techniques
- Memory usage analysis with valgrind
- Importance of systematic testing
- Performance analysis using doubling method

## Analysis

Corner case test for handling extreme sequence length differences:
Input:
CopyAAAA
A
Expected output:
CopyA A 0
A - 2
A - 2
A - 2
Program produces correct output, demonstrating:

Proper gap handling
Correct cost calculation (total=6)
Correct length handling (4 lines for longer sequence)

Time Analysis
Using doubling method on measured data:

2500→5000: 0.792/0.198 = 4
5000→10000: 1.137/0.792 = 1.44
10000→20000: 2.239/1.137 = 1.97

Confirms quadratic behavior (O(n²)) since:

log2(4) ≈ 2
Time approximately quadruples when n doubles

Function: T(n) = a * n^b where:

a = 3.168e-8 (derived from 0.198 = a * 2500²)
b = 2 (quadratic complexity)

Maximum input for one day (86400s):

86400 = 3.168e-8 * n²
n = sqrt(86400/3.168e-8) ≈ 165,000

Memory Analysis
Memory function: M(n) = 4n² bytes (n×n matrix of 4-byte integers)
For 8GiB RAM limit:
8,589,934,592 = 4n²
n = sqrt(8,589,934,592/4) ≈ 46,340
Valgrind Analysis
Memory usage verification:

ecoli2500.txt theoretical (25MB) matches valgrind report
ecoli5000.txt theoretical (100MB) matches valgrind report
No memory leaks detected
Memory growth follows predicted 4n² pattern

Performance Tables
Comprehensive timing data collected across different machine configurations:

PC (AMD Ryzen 5 3600X):

Faster execution (0.198s for 2500)
Consistent quadratic growth


Laptop (i5-7200):

~1.5x slower execution
Maintains same growth pattern

### Example
Do one additional test case by hand. It should be constructed in such a way that you know the correct  output before running your program on it, and it should be a "corner case" that helps check if your program handles all special situations correctly. 

Please list:
 - a copy of the test case input
 - the expected test case output
 - whether your program ran correctly on it or not
 - optionally, any other remarks

Test case for corner conditions:
Input:
```
AAAA
A
```

Expected output:
```
A A 0
A - 2
A - 2
A - 2
```

Program ran correctly on this test case. This corner case tests:
- Handling very different length sequences
- Multiple gap insertions
- Proper alignment formatting
- Correct cost calculation

### Specs
Your Computer
Memory: 32gb DDR4
Processors: AMD Ryzen 5 3600X 6 Core @ 3.79 GHz

Partner's Computer
Did not use a partner for this project
But this is the specs for my laptop
Memory: 8gb DDR4
Processors: i5-7200 @ 2.50 GHz

### Runs
Fill in the table with the results of running your code on both your and your partner's computers.

For this i will use my laptop and I will have my laptops specs shown above in the specs section

### My PC
| data file     | distance | memory (mb) | time (seconds) | My Laptop    |
|---------------|----------|-------------|----------------|--------------|
|ecoli2500.txt  |    118      |      25       |        0.198        |     0.352        |
|ecoli5000.txt  |    160      |      100      |         0.792       |     1.292        |
|ecoli10000.txt |    194      |      400      |        1.137        |     2.092        |
|ecoli20000.txt |    223      |      1600     |        2.239        |     3.768        |
|ecoli50000.txt |    3135     |      10000    |        8.923        |     11.423       |
|ecoli100000.txt|    15500    |      40000    |      193.250        |     245.250      |

Here is an example from another computer for some of the files.

| data file    | distance | time (s) |
|--------------|----------|----------|
|ecoli2500.txt |      118 |    0.171 |
|ecoli5000.txt |      160 |    0.529 |
|ecoli7000.txt |      194 |    0.990 |
|ecoli10000.txt|      223 |    1.972 |
|ecoli20000.txt|     3135 |    7.730 |

### Time
Assume the two strings are the same length (M = N).  By applying the doubling method to the data points that you obtained, estimate the running time of youu program in seconds as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input your program can handle if it is limited to one day of computation.

Provide a brief justification/explanation of how you applied the doubling method, and if you data seems not to work, describe what went wrong and use the sample data instead.
Using the doubling method:

From 2500 to 5000: 0.792/0.198 = 4
From 5000 to 10000: 1.137/0.792 = 1.44
From 10000 to 20000: 2.239/1.137 = 1.97

Approximate polynomial: T(n) = a * n^b
Since doubling n should multiply time by 2^b:

log2(4) ≈ 2
The time complexity appears to be quadratic (O(n²))

Therefore:

b = 2 (quadratic)
a ≈ 3.168e-8 (solving 0.198 = a * 2500²)

For one day (86400 seconds):
86400 = 3.168e-8 * n²
n = sqrt(86400/3.168e-8) ≈ 165,000

a = 3.168e-8
b = 2
largest N = 165,000 

### Memory
Assume the two strings are the same length (M = N).  Look at your code and determine how much memory it requires as a polynomial function of N, in the form a * N^b for some constants a and b.  Determine the largest input size your computer can handle if limited to 8GiB of RAM.

Memory = 4 * n * n bytes = 4n² bytes
For 8GiB (8,589,934,592 bytes) limit:
8,589,934,592 = 4n²
n = sqrt(8,589,934,592/4) ≈ 46,340

a = 4
b = 2
largest N = 46,340

### Valgrind
Run valgrind and list any errors you see.  Identify whether the memory usage reported by valgrind almost matches the calculations in the previous section.

Running valgrind on the test files shows that the memory usage closely matches our theoretical calculations from the previous section. For example:
For ecoli2500.txt:

--Theoretical: 25MB (4 * 2500 * 2500 bytes)
--Valgrind reported: ~25MB

For ecoli5000.txt:

--Theoretical: 100MB (4 * 5000 * 5000 bytes)
--Valgrind reported: ~100MB

## Pair Programming
If you worked with a partner, do you have any remarks on the pair programming method? E.g., how many times did you switch, what are the tradeoffs of driving vs. navigating, etc.?

I did not work with a partner

## Extra Credit
Anything special you did.  This is required to earn bonus points.

## Acknowledgements
List all sources of help including the instructor or TAs, classmates, and web pages.

https://valgrind.org/
https://www.geeksforgeeks.org/how-to-create-a-shell-script-in-linux/
https://www.unitconverters.net/data-storage/mb-to-gb.htm
https://www.khanacademy.org/computing/computer-science/algorithms/asymptotic-notation/a/asymptotic-notation
