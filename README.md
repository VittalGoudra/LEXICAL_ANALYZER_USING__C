# LEXICAL_ANALYZER_USING__C


# PROJECT OVERVIEW

I developed a Lexical Analyzer using C programming to analyze C source code and identify different types of tokens. The project reads a `.c` source file, processes its contents, removes comments and unnecessary spaces, and classifies the source code into meaningful tokens.

It performs lexical analysis by recognizing keywords, identifiers, constants, operators, special symbols, string constants, character constants, and preprocessor directives.

## PROJECT OBJECTIVE

The main objective of this project is to understand how a compiler performs the first phase of compilation, known as Lexical Analysis. It converts raw source code into a sequence of meaningful tokens that can be used by subsequent compiler phases.

## KEY FEATURES

- FILE VALIDATION:** Validates command-line arguments and checks whether the input file has a `.c` extension.
- FILE HANDLING:** Opens and reads the complete C source file using dynamic memory allocation.
- COMMENT REMOVAL:** Removes single-line (`//`) and multi-line (`/* */`) comments.
- SPACE REMOVAL:** Eliminates unnecessary spaces and handles formatting in the source code.
- TOKEN IDENTIFICATION:** Identifies and classifies different tokens present in the C program.
- KEYWORD RECOGNITION:** Identifies reserved C keywords.
- IDENTIFIER RECOGNITION:** Recognizes variable names and function names.
- CONSTANT IDENTIFICATION:** Recognizes numeric, string, and character constants.
- OPERATOR RECOGNITION:** Identifies arithmetic, relational, logical, assignment, bitwise, and other operators.
- SPECIAL SYMBOL IDENTIFICATION:** Recognizes symbols such as parentheses, braces, brackets, commas, and semicolons.
- PREPROCESSOR DETECTION:** Identifies preprocessor directives such as `#include` and `#define`.
- LINE NUMBER TRACKING:** Displays the corresponding source-code line number for identified tokens.

# WORKING PROCEDURE

1. Accepts a C source filename through command-line arguments.
2. Validates the filename and checks the `.c` extension.
3. Opens the source file and reads its contents.
4. Allocates memory dynamically to store the complete file content.
5. Removes single-line and multi-line comments.
6. Removes unnecessary spaces from the source code.
7. Scans the processed source code character by character.
8. Identifies and classifies each token based on its type.
9. Displays the token, its category, and the corresponding line number.
10. Releases allocated memory and closes the file after processing.

# TOKEN CATEGORIES

- Keywords
- Identifiers
- Numeric Constants
- String Constants
- Character Constants
- Operators
- Special Symbols
- Preprocessor Directives
- Invalid Tokens / Invalid Constants

# TECHNOLOGIES USED

- Programming Language: C
- Compiler: GCC
- IDE: Visual Studio Code
- Concepts: File Handling, Dynamic Memory Allocation, Pointers, Strings, Arrays, Functions, and Conditional Statements.

# APPLICATIONS

- Understanding the lexical analysis phase of a compiler.
- Learning how source code is converted into tokens.
- Understanding compiler design fundamentals.
- Building a foundation for syntax analysis and compiler development.

# OUTPUT IMAGES

# CONCLUSION

This project helped me understand the internal working of the lexical analysis phase of a compiler. It strengthened my knowledge of C programming, file handling, dynamic memory allocation, string processing, and character-by-character scanning.
