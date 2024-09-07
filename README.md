# Can't Believe It's Not C++!
*AKA my personal std, but almost every name and acronym are already taken*

## Includes
### defer.h
A simple defer macro that works like Zig's defer
### dict.h
A hashmap (specifically flatmap) implementation that only works with character slices as keys (string w/ length), so dict(ionary) was most appropriate
### list.h
A doubly-linked list which doesn't destruct node chains in otherwise destructive methods (allowing you to reuse node chains)
### print.h
Print macros like printfn (printf w/ newline), print (prints every given argument according to its type) ((also has a printn variant)), and their fprintX counterparts
### queue.h
A queue interface on top of the linked list, which restricts to adding to the back and taking from the front
### slice.h
Slices are just a pointer with a length... although they are really convenient
### stack.h
A stack interface on top of vector, which restrict to adding to the top and taking from the top, with some extra methods for Forth like stack manipulation
### util.h
Extra utility macro's that make your code more explicit, like the function-, private-, header-, ref keywords and pun_cast
### vector.h
A dynamic array implementation named according to C++, because I Can't Believe It's Not C++!

*checkout the examples*
