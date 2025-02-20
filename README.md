# Lexical Analyzer

## Project Overview
This project is a **Lexical Analyzer** implemented in C++ as part of the **Compiler Construction** course. The program reads an input file (`File.txt`), tokenizes the input, and performs basic syntax validation using a **Recursive Descent Parser**.

## Features
- Identifies and classifies tokens from the input source code.
- Supports **keywords, variables, operators, delimiters, and numbers**.
- Implements **Recursive Descent Parsing** for basic syntax validation.
- Uses a **symbol table** for token storage and lookup.

## Token Categories
The lexical analyzer recognizes the following token types:
- **Keywords**: `IF`, `ELSE`, `WHILE`, `DO`, `FOR`, `RETURN`, `BREAK`
- **Data Types**: `INT`, `FLOAT`, `STRING`
- **Operators**: `PLUS`, `MINUS`, `MULTIPLY`, `DIVIDE`, `EQUAL`, `INCREMENT`, `DECREMENT`
- **Delimiters**: `SEMICOLON`, `COLON`, `COMMA`, `PARENTHESIS`, `BRACKETS`
- **Comparison Operators**: `LESS_THAN`, `GREATER_THAN`, `EQUALITY`, `LESS_EQUAL`, `GREATER_EQUAL`
- **Identifiers**: `VARIABLE`
- **Literals**: `DIGIT`, `OUTPUT_STR`

## Implementation Details
### 1. **Token Structure**
Each token is represented by the `Token` structure, which includes:
- `token_var`: Enum value representing the token type.
- `Token_name`: The actual token string.
- `Token_value`: Optional numerical value (for digits).

### 2. **Symbol Table**
The program maintains a **symbol table** (`Symbol_table[table_size]`), which stores:
- Previously encountered tokens.
- Associated values if applicable.

### 3. **Recursive Descent Parsing**
The parser uses the following grammar rules:
- **Expression Parsing** (`E`, `E_dash`, `T`, `T_dash`, `F`) to handle mathematical expressions.
- **Conditional Statements** (`IF`, `ELSE`, `WHILE`, `DO` statements).
- **Assignment Checking** (`check_assignment` function validates variable assignments).

## How It Works
1. Reads input from `File.txt`.
2. Tokenizes the input and stores tokens in the symbol table.
3. Validates expressions and statements using recursive parsing.
4. Outputs **"String ACCEPTED"** if the input is valid, otherwise **"String REJECTED"**.

## How to Run
1. Compile the program using a C++ compiler:
   ```sh
   g++ lexical_analyzer.cpp -o lexical_analyzer
   ```
2. Create an input file `File.txt` with source code to analyze.
3. Run the program:
   ```sh
   ./lexical_analyzer
   ```

## Example Input (`File.txt`)
```
if (x == 10) {
    x = x + 1;
}
```

## Example Output
```
~~> .: ( Recursive Descent Parser ) :. <~~
File Input: if (x == 10) { x = x + 1; }

~~> .: ( String ACCEPTED ) :. <~~
```

## Future Improvements
- Implement additional **syntax validation**.
- Enhance the **symbol table with scope management**.
- Extend **support for functions and complex expressions**.

## Author
**Asfand** - Compiler Construction Project

