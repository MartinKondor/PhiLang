# Abstract Syntax Tree (AST) and Action Tree (AT)

## Commons

### Conditional expressions

Code:
```
a = 0
b = 10

if a < b
  a += 1
elseif b < 0
  b += 1  
else
  b -= 1
endif
```

AST of the above code:
```
a   b
|   |
=   =
|   |   
0   10 

   if
   |
   -----------------------
   |            |        |         
condition      body    elseif     
   |            |        |     
   |            |        --------------------
   |            |        |          |       |
   a            a     condition    body    else
   |            |        |          |       |
   <            +=       b          b       b
   |            |        |          |       |
   b            1        <          +=      -=
                         |          |       |
                         0          1       1
```

AT of the above AST:
```
a - = -> 0
b - = -> 10
a - = -> a + 1 (because the value of "a" didn't change)
```

### Loops

TODO
