# Library Management System (C++)

A CLI-based library manager for adding, searching, updating, and deleting books. Data is stored in a binary file format. Designed using modular C++.

## Features
- Add, update, delete, and view books
- Search by ID
- Sort by Title, Author, or Year
- Case-insensitive search
- Binary file storage (`library.dat`)
- Simple menu-based navigation

## Tech Used
- C++ with `fstream` for binary file I/O
- Vector and sorting using STL
- Header files for modular structure
- Clean CLI interface

## How to Run
```bash
g++ -std=c++17 main.cpp BST.cpp operations.cpp -o LibraryManagement
./LibraryManagement.exe
```
### Option 2: Run Precompiled `.exe`
> Download the `LibraryManagement.exe ` (Optional: `LibraryData.dat` for sample data in same directory)  
> Then double-click or run via terminal:
```bash
./LibraryManagement.exe
