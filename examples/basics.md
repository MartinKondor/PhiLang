# Basic language data types, syntax and properties

* The empty/nothing value is "null", it can be assigned.
* Arithmetic is the same as in Mathematics, with the exception that the multiplication works only with a "*" sign. The order of execution: /, *, %, +, -.
* No endline needed, if there is an additional ";" at the end of the line, it throws a syntax error. Unless it's a null value declaration.
* Variables are mutable and dynamically typed.
* Functions can be called with parentheses, or without them, if it is not ambiguous.

# Data types

## Number

```py
a = 1
b = 2

print 1
print 1.
print .1
print 0.1

# arithmetic
print a + b  # prints 3
print a - b  # prints -1
print a * b  # prints 2
print a / b  # prints 0.5
print 2 * a / b # prints 1
print a / b * 2 # prints 1
print a / (2*b) # prints 0.25
print 10 % b  # prints 0
```

## String

In their heart Strings are lists of characters.

```py
"something ..."
'something else ...'
"some" + "thing"  # concatenation

print "\""  # prints """
print "\\"  # prints "\"

print "1" * 5  # prints "11111"

i = 0
print "Number: {}" % i  # prints "Number: 0"

print "Number: {}, {}" % i, i + 1  # prints "Number: 0, 1"

print( "Number + String " + 12 )  # prints "Number + String 12"
```

### Properties

```py
.len()  # returns the length of the string
.index(value)  # returns the starting index of the "value", if the value is not found then it returns "null"
.lower()  # converts string to lowercase
.upper()  # converts string to uppercase
.strip()  # remove whitespaces from the begining and the end of the string
.split(delimiter)  # split into a list at the "delimiter" character's positions, not including the "delimiter" itself
```

## List/Array

```py
# these two means the same
list = [1, 2, 3]
list = 1, 2, 3

# when the list is *-ed it means it's an array, so it can't change it's length
*array = 1, 2, 3
# or
array* = 1, 2, 3

# these two returns the same
print(array)
print(list)
# which is: "[1, 2, 3]"

# list of lists, a matrix
matrix = [
  [1, 2, 3],
  [4, 5, 6]
]
matrix =
  1, 2, 3,
  4, 5, 6
matrix = 1, 2, 3,
  4, 5, 6
matrix = [[1, 2, 3], [4, 5, 6]]
# these has the same meaning

print matrix
# prints:
# [[1, 2, 3],
# [4, 5, 6]]
# the star operator also works for proper matrices (proper matrix: all of it's rows length are the same)

# lists can have multipe type of values
list = ["String", 1, 1., [0.1, 1, 10, 100]]
# arrays can't
array* = ["String", 1, 1., [0.1, 1, 10, 100]] # throws an error
```

### Properties

```py
.len()  # returns the length
.add(value)  # adds value to the list, only works with lists
.sum()  # adding up every value like
"""
Example:
list = 1, 2, 3, "String?"

print list.sum()
# prints 1 + 2 + 3 + "String?" so: "6String?"
"""
.remove(i)  # remove the ith element of the list, only works with lists
```

# Syntax

## Comments

```py
# one line comment 1
# one line comment 2

"""
Multi line comment
"""

"""
Multi line comment
Multi line comment
Multi line comment
"""
```

## Variable declaration

```py
a;  # create variable and assign "null" to it
a = null  # same as above
a  # throws an error
a = 0  # is fine
a = ""  # variables are mutable
```

## Statements and special expressions

```py
# TODO
```

## Functions

```py
# TODO
```
