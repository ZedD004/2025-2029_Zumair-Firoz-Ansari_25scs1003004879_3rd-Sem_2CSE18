# AI-Based Student Performance Predictor using C++

**Student:** HARSHIT SONI  
**Roll No.:** 25SCS1003004693  
**Program:** B.Tech (Computer Science & Engineering - Artificial Intelligence)  
**University:** IILM University, Greater Noida, U.P.

## Project Overview

This project is an educational AI application written in **C++17**. It predicts a student's performance category as **Low**, **Medium**, or **High** from four academic indicators:

- Attendance percentage
- Daily study hours
- Previous examination marks
- Assignment completion percentage

The project implements **k-Nearest Neighbours (k-NN)** from scratch using the C++ Standard Library. The program normalizes the features, calculates Euclidean distance from the query student to each labelled training record, selects the three nearest neighbours, and uses majority voting for the final class.

## Why this project?

The goal is to connect C++ programming fundamentals with an introductory machine-learning workflow without depending on external machine-learning frameworks. It demonstrates data representation, preprocessing, distance calculation, sorting, voting, input validation, and interpretable prediction.

## Features

- C++17 implementation
- k-NN classifier implemented from scratch
- Min-max feature normalization
- Euclidean-distance similarity calculation
- Majority voting with `k = 3`
- Input validation
- Optional training-data display
- Human-readable nearest-neighbour output

## Project Structure

```text
AI-Student-Performance-Predictor/
├── main.cpp
├── README.md
├── sample_output.txt
└── .gitignore
```

## How to Compile and Run

### g++

```bash
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o predictor
./predictor
```

### Windows (MinGW)

```bash
g++ -std=c++17 -O2 -Wall -Wextra main.cpp -o predictor.exe
predictor.exe
```

## Example Input

```text
Show training dataset? (y/n): n
Attendance (0-100): 79
Daily study hours (0-12): 4.2
Previous marks (0-100): 76
Assignments completed % (0-100): 82
```

The program then lists the nearest neighbours and prints a predicted category.

## Methodology

1. Store a small labelled training dataset.
2. Find minimum and maximum values for each feature.
3. Normalize the training records and the query record using min-max scaling.
4. Calculate Euclidean distance between the query and every training record.
5. Sort the records by distance.
6. Select the nearest `k = 3` records.
7. Count class votes and return the class with the highest vote count.

## Limitations

This repository contains a small, manually defined dataset intended for learning and demonstration. The output should **not** be treated as an official prediction of academic performance.

Possible next steps include CSV-based datasets, weighted k-NN, train/test evaluation, automatic `k` selection, additional features, a GUI, a database, or an API layer.

## Academic Context

This implementation corresponds to the B.Tech AI project report titled **“AI-Based Student Performance Predictor Using C++”**.
