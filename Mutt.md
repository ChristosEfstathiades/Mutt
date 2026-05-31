# Mutt

## Steps

1. lexical analyser - split tokens input into tokens
2. Parser - create AST according to grammar - recursive descent
3. Backend - Translates to C

## The Mutt Langauge

### Overview

- Static typed
- Manual memory management
- Variables immutable by default

### Data Types

#### Scalar types

- Booleans. true /false
- Intergers. unsigned: u8-64, signed: i8-64
- Floating-Point. f32, f64
- Strings. string
- Character. char
- Null. null

### Expressions

- No implicit conversions when comparing types

#### Logical Operators

!, and, or

### Control Flow

#### If Expressions

- no brackets in if statements
- if condition {}

#### Loops

- no brackets in for/while loops
- iterator based like python

cmake -S . -B build -G Ninja
cmake --build build

gcc out.c -I./include -o output
