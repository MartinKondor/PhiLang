# PhiLang
[![version](https://img.shields.io/badge/version-v0.1.0-red.svg)](https://github.com/MartinKondor/PhiLang) [![Project Status](https://img.shields.io/badge/status-prototype-red.svg)](https://github.com/MartinKondor/PhiLang)

PhiLang is a general-purpose programming language designed for running Machine Learning and Deep Learning programs.

The goal is to make a programming language that:

- [ ] Easy to use, it let's you think about the algorithm instead of code writing.
- [ ] Executes faster than Python, R, Octave, Matlab and other competitors.
- [ ] Can be easily accessed and runned from other programming languages.
- [ ] Contains the basic ML and DL algorithms.

## How the interpreter works

When running a program, this is what happens:

- [ ] The parser reads the program text and makes a parse tree. Finds syntax errors, figures out statements and expressions.
- [ ] The parse tree is converted to Java objects.
- [ ] Semantic analysis of the parse tree -- finds semantic errors, type errors, resolves types, figures out lexical scopes resolves variable names.
- [ ] Code generation -- converts the AST to byte code, in Phi's custom format.
- [ ] Byte code interpretation -- executes the byte code.

Between each of the above steps there is one value that defines the entire program. This value is in JSON format or can be convert to/from JSON format. This makes it simple to insert tools along the way or skip or replace steps all together.

### Parser

The parser reads a Phi program as a text file and outputs a parse tree encoded as JSON. It understands function definitions, complex expressions with parenthesis and brackets etc. It figures out evaluation order of expressions.

The parser is designed so it can be used on its own. This makes it simple to create tools for Phi. All information from the program text is preserved inside the parser output, except formatting and comments.

## Data types

* Object = Abstract base object that every other object extends.
* Number = In other languages it's int, float, double.

## Language syntax

Phi is dynamically typed, all variables are mutable.
It's got built in types for vectors, matrices, dictionaries, JSON, and strings.

## License

Copyright (C) Martin Kondor 2019

See the `LICENSE` file for more details.
