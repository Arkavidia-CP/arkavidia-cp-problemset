# Arkavidia CP Problemset

Collection of Arkavidia CP (_Competitive Programming_) Problemset since $2019$.

## Project structure


```
├── <arkavidia-year>
|   ├──<problem-name>               // The Problem Name
|   |   ├── tc                      // Folder test cases
|   │   ├── solution.cpp            // Main Solution
|   │   ├── alt-solution.cpp        // Alternative Solutions (could be more than one)
|   |   ├── spec.cpp                // Problem specification build in tcframe
|   │   ├── tutorial.md             // Tutorial written in markdown (if needed)
|   |   ├── statement.tex           // Problem in LaTeX
└── └── └── statement.pdf           // Problem in PDF
```

## General Guide

Here are some general guides on preparing Arkavidia CP Problems:

1. Make clear and readable statements, use LaTeX for every variable and mathematics involved, and use the proper format for classic CP Contest (See CodeForces rounds or ICPC contests).

1. Try to make a balanced contest by estimating difficulty and tags. 

1. Create tight testcases, try not to make too many random testcases.

## Notes

Templates in creating problem statement: `template.tex`

Use the script `generate-problem.sh` to generate test data and PDF statement.
