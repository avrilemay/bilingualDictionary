# English-Spanish Dictionary

### Description
This project is a command-line English-Spanish dictionary built in C. The dictionary allows users to search for the Spanish translations of English words, along with their grammatical categories. The project employs data structures to manage and retrieve dictionary entries efficiently.

This project was developed by Avrile Floro.

### Features
- **Data Structure Management:** Implements custom data structures to store and retrieve dictionary entries.
- **Word and Category Parsing:** Processes both the English word and its grammatical category.
- **Translation Retrieval:** Returns all possible Spanish translations for a given English word.
- **Testing Capabilities:** Includes a set of tests to verify the dictionary's accuracy and functionality.

### Files Overview
- **`sys.h`:** Contains essential library imports and system configurations used across the project.
- **`structure.h`:** Defines the data structures and function prototypes required for the dictionary operations.
- **`dictionnaire.c`:** The main program file that includes the core logic for loading the dictionary and translating words.
- **`category.c`:** Manages the assignment of numerical identifiers to grammatical categories.
- **`test.c`:** Handles the creation and execution of tests to ensure the dictionary works as expected.
- **`makefile`:** Automates the build process for compiling the dictionary program.
- **`makefile_tests`:** Automates the build process specifically for running the tests.

### Usage
To compile and run the dictionary:

```bash
make
./dictionnaire
```

For running the tests:
```bash
make -f makefile_tests
./dictionnaire_test
```
