# Inventory_System
This is a university assignment that required us to implement an inventory system that uses a doubly-linked list and quicksort. It is all written in C++.

Contents:
---------
1. Source
  - All source code files (.cpp and .h)
  - Inventory.txt (input file)
  - These are needed to compile the program

2. Release
  - Compiled binary ("inventory" on Linuc/macOS or "inventory.exe" on Windows)
  - Inventory.txt (input file required at runtime)
  - This allows the program to run without compiling.

Instructions for Running the Program:
-------------------------------------

A) Using the Release Version:
1. Extract Release.zip into a folder.
2. Ensure that Inventory.txt is in the same folder as the binary/exe file.
3. Run the program:
   
  Linux/macOS:
  ------------
  Open the terminal in the Release folder and execute:
  ./inventory

  Windows:
  --------
  Open command prompt in the Release folder and execute:
  inventory.exe

B) Compiling from Source.zip (if Release binary is not compatible):
1. Extract Source.zip to a folder.
2. Ensure that you have a C++ compiler installed:
  - Linux/macOS: g++ or clang++
  - Windows: MinGW or MVSC
3. Open a terminal/command prompt in the source folder.
4. Compile the program using:

  Linux/macOS:
  ------------
  g++ main.cpp cInventory.cpp cInventoryIO.cpp eItemType.cpp -o inventory

  Windows (MinGW):
  ----------------
  g++ main.cpp cInventory.cpp cInventoryIO.cpp eItemType.cpp -o inventory.exe

5. After compilation, ensure Inventory.txt is in the same folder as the binary/exe.
6. Run the program:

  Linux/macOS:
  ------------
  ./inventory

  Windows:
  --------
  inventory.exe

Notes:
------
- Inventory.txt must always be in the same folder as the execute for the program to read it correctly.
- If the program does not run, ensure that your OS allows execute permissions:
  - Linux/macOS: Run 'chmod +x inventory' to make it executable.
- No additional libraries are required beyond the standard C++ library.
