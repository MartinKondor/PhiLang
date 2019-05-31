<p align="center">
  <img src="https://github.com/MartinKondor/PhiLang/blob/master/docs/logo.png" width="450">
</p>

# PhiLang
[![version](https://img.shields.io/badge/version-2019.06-red.svg)](https://github.com/MartinKondor/PhiLang) [![Project Status](https://img.shields.io/badge/status-prototype-red.svg)](https://github.com/MartinKondor/PhiLang) [![License](https://img.shields.io/badge/license-MIT-green.svg)](https://github.com/MartinKondor/PhiLang/edit/master/LICENSE)

Phi is a general-purpose programming language designed for writing the most readable and most understandable programs, which yet they are powerfull enough to run webservers, io operations, and even microcontrollers. The only requirement for writing a program with Phi is that you must know how to read plain English text.

Development goals:

- [x] Do TDD
- [x] Use OOP
- [ ] Use some sort of CI
- [ ] Issue tracking

Goals:

* Easy to use, it let's you think about the algorithm instead of code writing. Phi is [sweet syntactically](https://en.wikipedia.org/wiki/Syntactic_sugar).
* Executes faster than Python, R, Octave, Matlab and other competitors.
* Can be easily accessed and runned from other programming languages.
* Contains the general algorithms.
* Have an option to be compiled to bytecode, for running low level operations.

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

Fork repository, make changes, send us a pull request. We will review your changes and apply them to the master branch shortly, provided they don't violate our [quality standards](https://github.com/MartinKondor/PhiLang/blob/master/docs/CODE_OF_CONDUCT.md) and the our [style guide](https://github.com/MartinKondor/PhiLang/blob/master/docs/CODE_STYLE_GUIDE.md).

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
