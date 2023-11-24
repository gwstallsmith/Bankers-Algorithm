# Banker's Algorithm Implementation in C++

## Overview
This project contains a C++ implementation of the banker's algorithm, a deadlock avoidance algorithm used in operating systems. The algorithm ensures that a system avoids deadlock by safely allocating resources to processes based on their needs.

## Features
- **Resource Allocation**: Demonstrates how resources are allocated to processes in a safe manner.
- **Deadlock Avoidance**: Prevents deadlock situations by analyzing the available resources before allocating them to processes.
- **Safety Check**: Verifies the safety of resource allocation to maintain a safe system state.

## Requirements
- C++ compiler supporting C++11 or higher

## Usage
1. Clone the repository:
    ```bash
    git clone https://github.com/gwstallsmith/Bankers-Algorithm
    ```
2. Navigate to the project directory:
    ```bash
    cd Bankers-Algorithm
    ```
3. Compile the C++ program:
    ```bash
    g++ -std=c++11 bankers.cpp -o bankersAlgorithm
    ```
4. Run the executable:
    ```bash
    ./bankersAlgorithm example.txt
    ```
5. Follow the prompts to input the number of processes, resources, allocation matrix, and maximum matrix.

## Example
Suppose you have 5 processes and 3 resources. You'll be prompted to input the allocation matrix and maximum matrix for processes and resources. The program will output whether the system is in a safe state and if so, demonstrate the order in which processes can complete their execution safely.
