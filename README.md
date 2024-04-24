# POS C++ Project

This repository contains a C++ implementation of a Point of Sale (POS) system, designed to manage sales transactions and inventory in a retail environment.

## Structure

Below is an outline of the project's directory structure and descriptions of each file:

- `*.cpp` and `*.h` - Source and header files for the POS system's various classes and functionalities.
- `README.md` - The file you're currently reading that provides documentation for the project.
- `Ulis.cpp` and `Ulis.h` - Utility library files for shared functionality across the project.
- `ms*.output.txt` - Output files from sample runs of the system (ms1 to ms5 likely represent different milestones or test scenarios).
- `main.cpp` - The main entry point of the POS application.

### Source Files

- `Bil.cpp/h` - Handles the billing functionality.
- `Date.cpp/h` - Manages date-related operations (Used in perishable items.).
- `Error.cpp/h` - Error handling components.
- `Item.cpp/h` - Defines the item structure and related operations.
- `NonPerishable.cpp/h` - Inherits Item Class and specifies implementation for non-perishable items.
- `Perishable.cpp/h` - Inherits the Item Class and specifies implementation for perishable items.
- `POSApp.cpp/h` - Main application logic for user interaction.
- `PosIO.cpp/h` - Input/Output operations for the POS system.

### Utility Files

- `Ulis.cpp/h` - Contains utility functions that assist with common operations within the POS system.

### Data Files

- `posdataorigin.csv` - Data file used by the POS system, likely for storing inventory or transaction data.
- `posdata.csv` - Stores data necessary for POS operations, such as inventory lists.

### Documentation Files

- `README.md` - Documentation for understanding and navigating the project.

### Output Files

- `ms1_output.txt` to `ms5_output.txt` - Sample output from tests conducted during various development milestones.

## Setup

Instructions on how to compile and run the POS system:

```bash
g++ *.cpp -std=c++11 -o pos.exe
./POS
