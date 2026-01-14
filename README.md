Just easy experiment to see how the Brainfuck interpreter works. Added some more functionality, and also a trasnpiler that converts the code into C++.

Use like:
```
./tom.sh source.tom     #first transpiles to C++ and then compiles a binary with g++
```
Use space or new line between keywords.

Transpiler examples:
```
string hi = "inc 8 while right inc 9 left dec 1 end right print inc 33 print";
string test = "inc 47 while print dec 1 end";
string asterisk = "inc 42 repeat 5 print end";

interpret(hi)
interpret(test)
interpret(asterisk)
```

Compiler example found in tom.source.

Keywords for interpreter:
- `inc` -> increments value pointed at by pointer
- `dec` -> decrements value pointed at by pointer
- `left` -> moves pointer to the left
- `right` -> moves pointer to the right
- `repeat x` -> repeats a command x times 
- `while` -> repeats a command until value under pointer is 0
- `end` -> marks end of loop block
- `get` -> prompts user input
- `set x` -> set value underneath pointer to x
- `copy x` -> sets value underneath pointer to the value underneath (pointer + x)
- `print` -> prints ASCII value of current value underneath pointer
- `out` -> prints literal value underneath pointer
- `dump` -> prints first few values of tape

Keywords for transpiler: 
- `inc` -> increments value pointed at by pointer
- `dec` -> decrements value pointed at by pointer
- `left` -> moves pointer to the left
- `right` -> moves pointer to the right
- `repeat x` -> repeats a command x times 
- `while` -> repeats a command until value under pointer is 0
- `print` -> prints ASCII value of current value underneath pointer
- `out` -> prints literal value underneath pointer


Todo:
- add variables with a symbols map
- add arithmetic
- translate to assembly?
