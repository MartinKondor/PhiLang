# Basic language data types, syntax and properties

* The empty/nothing value is "null", it can be assigned.
* Arithmetic is the same as in Mathematics, with the exception that the multiplication works only with a "*" sign. The order of execution: /, **, *, %, +, -.
* No endline needed, if there is an additional ";" at the end of the line, it throws a syntax error. Unless it's a null value declaration.
* Variables are mutable and dynamically typed.
* Functions can be called with parentheses, or without them, if it is not ambiguous.

# Keywords

```
if, else, elseif, 
while, for, in,
continue, break,
true, false, null,
and, or, not,
def, return, const,
try, catch, throw,
as, import, delete,
finally, is, pass,
yield
```

# Data types

## Boolean

```
a = ture
b = false

a and b  # and expression
a or b  # or expression
10 == 0  # returns a Boolean, false
10 != 0  # returns a Boolean, true
# also does: <, >, <=, >=
```

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
print 10 ** 2  # prints 100
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
[i]  # get the ith element of the list/array, starts from 0 
```

# Syntax and built in functions

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

Generaly:
```ruby
statement [expression(s)]
  # statement body
end[statement]
```
So, the if statement.
```
if true
  pass
endif

if true
  pass
else
  pass
endif

if true
  pass
elseif
  pass
else
  pass
endif
```

The for loop
```
for i in list
  pass
endfor

# yes, an N Number can be iterated from 0 to N inclusive on both sides
for i in 10
  pass
endfor
"""
How?

(i in 10) means -> (i in [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10])
"""

# iterate from 5 to 10 inclusive on both sides
for i in 5, 10
  pass
endfor

# iterate from 5 to 10 inclusive on both sides with steps 0.5
for i in (5, 10, .5)
  pass
endfor

for i = 0; i < list.len(); i++
  list[i]
endfor
```

While, the second one is working like the traditional `do {...} while (...)` loop
```
while true
  pass
endwhile

# or
while
  pass
endwhile true
```

## Functions

```
def function(x)  # declaration with name
  pass # does nothing
  return x  # return statement
enddef

# inline function declaration
function = def (x)  x**2  enddef  # returns x**2

# inline function declaration can be extended to
function = def (x)
  return x**2
enddef

# more parameters and no return statement
def func(a, b, c)
  pass  
enddef

def(x)
  pass
enddef(some_parameter)  # this is valid, unnamed function called immediately
```
