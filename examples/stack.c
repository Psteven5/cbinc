#include "../all"

/* https://wiki.c2.com/?ExampleForthCode */

private struct stack(uintptr_t) stack = {};

private function void emit(void) {
    var const result = stack__top(uintptr_t, stack);
    if (NULL == result)
        return;
    char const c = *result;
    stack__pop(uintptr_t, NULL, stack);

    print(c);
}

private function void star(void) {
    stack__push(uintptr_t, 42, stack);
    emit();
}

private function void stars(void) {
    var const result = stack__top(uintptr_t, stack);
    if (NULL == result)
        return;
    var const n = *result;
    stack__pop(uintptr_t, NULL, stack);

    for (uintptr_t _ = n; 0 != _; --_)
        star();
}

private function void square(void) {
    stack__duplicate(uintptr_t, stack);

    var const result = stack__top(uintptr_t, stack);
    if (NULL == result)
        return;
    var const n = *result;
    stack__pop(uintptr_t, NULL, stack);

    for (uintptr_t _ = n; 0 != _; --_) {
        stack__duplicate(uintptr_t, stack);
        stars();
        printn("");
    }
}

private function void triangle(void) {
    var const result = stack__top(uintptr_t, stack);
    if (NULL == result)
        return;
    var const n = *result;
    stack__pop(uintptr_t, NULL, stack);

    for (uintptr_t i = 1; i < n + 1; ++i) {
        stack__push(uintptr_t, i, stack);
        stars();
        printn("");
    }
}

private function void sub(intptr_t b) {
    var const result = stack__top(uintptr_t, stack);
    if (NULL == result)
        return;
    var const a = *result;
    stack__pop(uintptr_t, NULL, stack);

    stack__push(uintptr_t, a - b, stack);
}

private function void tower(void) {
    stack__duplicate(uintptr_t, stack);
    sub(1);
    triangle();
    square();
}

function int main(void) {
    stack__push(uintptr_t, 7, stack);
    stars();
    printn("");

    stack__push(uintptr_t, 3, stack);
    triangle();

    stack__push(uintptr_t, 6, stack);
    tower();

    stack__destroy(uintptr_t, NULL, stack);
}