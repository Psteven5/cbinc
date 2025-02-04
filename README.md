# Can't Believe It's Not C++!
> *AKA my personal std extension, but almost every name and acronym are already taken*
---
> [Check out the examples](examples/)

*Includes and Usages:*
* [defer.h](#deferh)
* [dict.h](#dicth)
* [list.h](#listh)
* [print.h](#printh)
* [queue.h](#queueh)
* [slice.h](#sliceh)
* [stack.h](#stackh)
* [util.h](#utilh)
* [node.h](#nodeh)
* [vector.h](#vectorh)

## Includes & Usages
### [defer.h](defer.h)
A simple defer macro that works like Zig's defer
```C
#include <stdio.h>
#include "defer.h"

void cleanup(int *dummy) {
    printf("Deferred function called.\n");
}

int main() {
    defer {
        printf("This will be printed last.\n");
    }
    printf("This will be printed first.\n");
    return 0;
}
```
#### Explanation:
* The `defer` macro allows you to execute a function when the scope ends.
* In this example, the deferred code block will execute `cleanup` when `main` exits.
### [dict.h](dict.h)
A hashmap (specifically flatmap) implementation that only works with character slices as keys (string w/ length), so dict(ionary) was most appropriate
```C
#include <stdio.h>
#include <string.h>
#include "dict.h"

int main() {
    struct dict(int) my_dict = dict__create(int);

    // Insert key-value pairs
    dict__insert(int, slice__create(char, "one", 3), 1, my_dict);
    dict__insert(int, slice__create(char, "two", 3), 2, my_dict);

    // Search for a key
    int *value = dict__search(int, slice__create(char, "one", 3), my_dict);
    if (value) {
        printf("Value for 'one': %d\n", *value);
    }

    // Delete a key
    dict__delete(int, slice__create(char, "two", 3), NULL, my_dict);

    // Destroy the dictionary
    dict__destroy(int, NULL, my_dict);
    return 0;
}
```
#### Explanation:
* Creates a dictionary mapping strings to integers.
* Demonstrates insertion, search, deletion, and destruction.
### [list.h](list.h)
A doubly-linked list which doesn't destruct node chains in otherwise destructive methods (allowing you to reuse node chains)
```C
#include <stdio.h>
#include "list.h"

int main() {
    struct list(int) my_list = list__create(int);

    // Push elements to the list
    list__push_back(int, 10, my_list);
    list__push_back(int, 20, my_list);
    list__push_front(int, 5, my_list);

    // Iterate through the list
    for (struct node(int) *node = my_list.begin; node != NULL; node = node->right) {
        int *value = node__access(int, node);
        printf("%d ", *value);
    }
    printf("\n");

    // Destroy the list
    list__destroy(int, NULL, my_list);
    return 0;
}
```
#### Explanation:
* Demonstrates how to create a list, add elements to both ends, iterate, and destroy it.
### [print.h](print.h)
Print macros like printfn (printf w/ newline), print (prints every given argument according to its type) ((also has a printn variant)), and their fprintX counterparts
```C
#include "print.h"

int main() {
    int a = 10;
    float b = 3.14;
    char *str = "Hello, World!";
    bool flag = true;

    printn("Integer: ", a);
    printn("Float: ", b);
    printn("String: ", str);
    printn("Boolean: ", flag);

    return 0;
}
```
#### Explanation:
* Uses printn macro to print different data types without specifying format specifiers.
### [queue.h](queue.h)
A queue interface on top of the linked list, which restricts to adding to the back and taking from the front
```C
#include <stdio.h>
#include "queue.h"

int main() {
    struct queue(int) my_queue = queue__create(int);

    // Enqueue elements
    queue__push(int, 1, my_queue);
    queue__push(int, 2, my_queue);
    queue__push(int, 3, my_queue);

    // Dequeue elements
    while (!queue__is_empty(int, my_queue)) {
        int *value = queue__front(int, my_queue);
        printf("Dequeued: %d\n", *value);
        queue__pop(int, my_queue);
    }

    // Destroy the queue
    queue__destroy(int, NULL, my_queue);
    return 0;
}
```
#### Explanation:
* Demonstrates enqueueing and dequeueing elements in a queue.
* Shows how to check if the queue is empty and how to destroy it
### [slice.h](slice.h)
Slices are just a pointer with a length... although they are really convenient
```C
#include <stdio.h>
#include "slice.h"

int main() {
    int array[] = {1, 2, 3, 4, 5};
    struct slice(int) my_slice = slice__create(int, array, 5);

    // Access elements using slice
    for (size_t i = 0; i < my_slice.size; ++i) {
        int *value = slice__access(int, i, my_slice);
        printf("%d ", *value);
    }
    printf("\n");

    return 0;
}
```
#### Explanation:
* Creates a slice over an existing array.
* Demonstrates element access within the slice.
### [stack.h](stack.h)
A stack interface on top of vector, which restricts to adding to the top and taking from the top, with some extra methods for Forth like stack manipulation
```C
#include <stdio.h>
#include "stack.h"

int main() {
    struct stack(int) my_stack = stack__create(int);

    // Push elements onto the stack
    stack__push(int, 10, my_stack);
    stack__push(int, 20, my_stack);
    stack__push(int, 30, my_stack);

    // Duplicate the top element
    stack__duplicate(int, my_stack);

    // Swap the top two elements
    stack__swap(int, my_stack);

    // Pop elements from the stack
    while (!stack__is_empty(int, my_stack)) {
        int *value = stack__top(int, my_stack);
        printf("Popped: %d\n", *value);
        stack__pop(int, NULL, my_stack);
    }

    // Destroy the stack
    stack__destroy(int, NULL, my_stack);
    return 0;
}
```
#### Explanation:
* Demonstrates stack operations like push, pop, duplicate, and swap.
* Shows how to access the top element and check if the stack is empty.
### [util.h](util.h)
Extra utility macro's that make your code more explicit, like the function-, private-, header-, ref keywords and pun_cast
```C
#include <stdio.h>
#include "util.h"

int main() {
    int a = 5;
    int b = 10;

    // Using 'var' to automatically deduce type
    var sum = a + b;
    printf("Sum: %d\n", sum);

    // Using 'pun_cast' to reinterpret bits
    float f = 3.14f;
    int bits = pun_cast(int, f);
    printf("Bits of 3.14f: %x\n", bits);

    return 0;
}
```
#### Explanation:
* Demonstrates the use of utility macros like var for type deduction and pun_cast for type punning.
### [node.h](node.h)
```C
#include <stdio.h>
#include "node.h"

int main() {
    // Create nodes
    struct node(int) *node1 = node__create(int);
    struct node(int) *node2 = node__create(int);

    // Set data
    *node__access(int, node1) = 100;
    *node__access(int, node2) = 200;

    // Link nodes
    node1->right = node2;
    node2->left = node1;

    // Access data
    printf("Node1 data: %d\n", *node__access(int, node1));
    printf("Node2 data: %d\n", *node__access(int, node2));

    // Destroy nodes
    node__destroy(int, NULL, node1);

    return 0;
}
```
#### Explanation:
* Shows how to create nodes, set data, link them, and destroy.
### [vector.h](vector.h)
A dynamic array implementation named according to C++, because I Can't Believe It's Not C++!
```C
#include <stdio.h>
#include "vector.h"

int main() {
    struct vector(int) my_vector = vector__create(int);

    // Reserve space
    vector__reserve(int, 5, my_vector);

    // Push back elements
    for (int i = 1; i <= 5; ++i) {
        vector__push_back(int, i * 10, my_vector);
    }

    // Access elements
    for (size_t i = 0; i < my_vector.size; ++i) {
        int *value = vector__access(int, i, my_vector);
        printf("%d ", *value);
    }
    printf("\n");

    // Delete an element
    vector__delete(int, (char *)vector__access(int, 2, my_vector), 1, NULL, my_vector);

    // Access elements after deletion
    for (size_t i = 0; i < my_vector.size; ++i) {
        int *value = vector__access(int, i, my_vector);
        printf("%d ", *value);
    }
    printf("\n");

    // Destroy the vector
    vector__destroy(int, NULL, my_vector);
    return 0;
}
```
#### Explanation:
* Shows how to create a vector, reserve space, push elements, access, delete, and destroy.
