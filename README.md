# PhiLang

PhiLang is a general-purpose programming language designed for running Machine Learning programs.

The goal is to make a programming language that:

* Executes faster than Python, R, Octave, Matlab and other competitors.
* Can be easily accessed and runned from other programming languages.
* Contains the basic ML and DL algorithms.

## How the interpreter works

When running a program, this is what happens:

[] The parser reads the program text and makes a parse tree. Finds syntax errors, figures out statements and expressions.
[] The parse tree is converted to Java objects.
[] Semantic analysis of the parse tree -- finds semantic errors, type errors, resolves types, figures out lexical scopes resolves variable names.
[] Code generation -- converts the AST to byte code, in Phi's custom format.
[] Byte code interpretation -- executes the byte code.

Between each of the above steps there is one value that defines the entire program. This value is in JSON format or can be convert to/from JSON format. This makes it simple to insert tools along the way or skip or replace steps all together.

## Data types

Number = int, float both 64 and 32 bits

## Language syntax

Phi is Dynamically typed, all variables are mutable.
It's got built in types for vectors, matrices, dictionaries, JSON, and strings.

## License

Copyright (C) Martin Kondor 2019
See the `LICENSE` file for more details.
