<p align="center">
  <img src="https://github.com/MartinKondor/PhiLang/blob/master/docs/logo.png" width="450">
</p>

# PhiLang
[![version](https://img.shields.io/badge/version-2019.06-red.svg)](https://github.com/MartinKondor/PhiLang) [![Project Status](https://img.shields.io/badge/status-prototype-red.svg)](https://github.com/MartinKondor/PhiLang) [![License](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/MartinKondor/PhiLang/edit/master/LICENSE)

Phi is a general-purpose programming language designed for writing the most readable and most understandable programs, which yet they are powerfull enough to run webservers, io operations, and even microcontrollers. The only requirement for writing a program with Phi is that you must know how to read plain English text.

Goals:

* Easy to use, it let's you think about the algorithm instead of code writing. Be [sweet syntactically](https://en.wikipedia.org/wiki/Syntactic_sugar).
* Executes faster than Python, R, Octave, Matlab and other competitors.
* Can be easily accessed and runned from other programming languages.
* Contains the basic ML and DL algorithms.
* Have an option to be compiled to bytecode, for running low level operations.

## How the interpreter works

When running a program, this is what happens:

- [X] Parser reads the program text.
- [X] Lexer makes a parse tree (AST). Finds syntax errors, recognize out statements and expressions, save tokens to the AST.
- [ ] Parser makes semantic analysis of the parse tree -- finds semantic errors, type errors, resolves types, figures out lexical scopes resolves variable names. Creates Concrete Syntax Tree (CST).
- [ ] Executes the code according to the CST.

### Parser

The parser reads a Phi program as a text (1) and figures out evaluation order of expressions according to the AST. (3)

The parser adds structure to to the AST tokens then produces and creates a Concrete Syntax Tree or CST. (4)

### Lexer

Finds syntax errors, recognize statements and expressions, saves tokens in the AST. (2)

### Abstract Syntax Tree (AST)

Does not have any info about types or which identifiers are which. It is simply structured tokens built by the lexer.

As an example if the code is:
```
a = 0
print(a, 10)
```
Then AST would look something like this:
```
  a (variable)    print (function)
  |                 |
  |                 |
  = (operator)   ------------------ (parameters)
  |              |                |
  |              |                |
  0 (Number)     a (variable)     10 (Number)
```

### Concrete Syntax Tree (CST)

The AST with context. That context is info such as what type a function returns, or that two places in which a variable is used are in fact using the same variable.

When running it, each action node has a function `execute` which takes some input, does whatever the action should (including possibly calling sub action) and returns the action's output. This is the interpreter in action.

A CST from the above example's AST:
```
a (declare varialbe with value) --> 0
print (function call) --> 0 (the variable 'a' maps to 0 at this line), 10 --> "0 10" (executed function output)
```

## Data types

### Types

A type is a _contract_ an object must obey.

A type is very similar to interfaces from Java. A type has a name a list of method declarations, and a list of attributes.

### Default types

* Object = Abstract base object that every other type extends in order to have some standardized methods.
* Number = In other languages it's int, float, double.
* Boolean = true or false.
* String = "..." or '...'.
* List = Can contain any type, elements can be added and removed.
* Array = Contains only one type, fixed size.

## Language syntax

Phi is dynamically typed, all variables are mutable.
It's got built in types for vectors, matrices, dictionaries, JSON, and strings.

For more, please read the `examples/README.md` file.

## How to contribute

Fork repository, make changes, send us a pull request. We will review your changes and apply them to the master branch shortly, provided they don't violate our [quality standards](https://github.com/MartinKondor/PhiLang/blob/master/CODE_OF_CONDUCT.md).

## Repository structure

```
examples/  # example Phi programs and the basic description of the language in the README.md file
src/  # Source files of the interpreter
lib/  # Libraries
docs/  # descriptions
```

## License

Copyright (C) Martin Kondor 2019

This Phi documentation, examples and the interpreter is distributed under [The MIT License](http://www.opensource.org/licenses/MIT).

See [LICENSE](https://github.com/MartinKondor/PhiLang/blob/master/LICENSE) for details.
