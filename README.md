# F(x)

A C++ equation solver that parses and evaluates mathematical expressions with a single variable (`x`).  
It finds and approximates one root within a given range using scanning and binary search.

## Features
Expression Parsing: Supports +, -, *, /, and power (^).  
Floating-Point Support: Handles decimal values.  
Root Finding: Locates one root within a specified range.  
Binary Search: Approximates the root with good precision.  

## Optimization

### Root Finding Optimization (Bisection Method)
Instead of brute-force search, the project uses the **bisection method (binary search on the function range)** after detecting a valid interval.
**Why it’s better:**
- Reduces complexity to **O(log n)** instead of **O(n^2)**  
- Much faster than linear scanning  

### Smart Interval Detection
Before applying bisection, the program scans the range with a fixed step to find a sign change interval.
**Why it’s better:**
- Prevents running binary search on invalid ranges  
- Reduces unnecessary function evaluations  
- Improves overall efficiency  

## How It Works
User enters an equation equal to 0.  
User provides a range (l, r).  
Program scans the range to find a valid interval.  
Binary search is applied to approximate the root.

## Usage
You can just download the file "fx.exe" and run it.
Then enter an equation which shoud equal to 0. 
Example:-
2x-4 (true).
2x=4 (false).
Then enter the range which are two numbers you want to find the root between.
Example:-
100 1000 (the left should be smaller than the right).
