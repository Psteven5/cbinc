#ifndef CBINC_STACK_H
#define CBINC_STACK_H

#include "vector.h"

#define stack(T) vector(T)

#define stack__duplicate(T, self) do {     \
    stack__duplicate_(sizeof(T), &(self)); \
} while (0)

#define stack__over(T, self) do {     \
    stack__over_(sizeof(T), &(self)); \
} while (0)

#define stack__swap(T, self) do {           \
    T tmp;                                  \
    stack__swap_(sizeof(T), &tmp, &(self)); \
} while (0)

#define stack__rotate(T, self) do {           \
    T tmp;                                    \
    stack__rotate_(sizeof(T), &tmp, &(self)); \
} while (0)

#define stack__create(T)              vector__create(T)

#define stack__push(T, x, self)       vector__push_back(T, (x), (self))

#define stack__pop(T, dtor, self)     vector__pop_back(T, (dtor), (self))

#define stack__destroy(T, dtor, self) vector__destroy(T, (dtor), (self))

#define stack__begin(T, self)         vector__begin(T, (self))

#define stack__end(T, self)           vector__end(T, (self))

#define stack__rbegin(T, self)        vector__rbegin(T, (self))

#define stack__rend(T, self)          vector__rend(T, (self))

#define stack__bottom(T, self)        vector__first(T, (self))

#define stack__top(T, self)           vector__last(T, (self))

#define stack__is_empty(T, self)      vector__is_empty(T, (self))

header function void stack__duplicate_(size_t T, struct stack(T) ref self)
{
    if (stack__is_empty(T, deref self))
        return;
    vector__insert_(T, (char *)self->data + self->size * T, (struct slice(T)) {(char *)self->data + (self->size - 1) * T, 1}, self);
}

header function void stack__over_(size_t T, struct stack(T) ref self)
{
    if (self->size < 2)
        return;
    vector__insert_(T, (char *)self->data + self->size * T, (struct slice(T)) {(char *)self->data + (self->size - 2) * T, 1}, self);
}

header function void stack__swap_(size_t T, void *tmp, struct stack(T) ref self)
{
    if (self->size < 2)
        return;
    memcpy(tmp, (char *)self->data + (self->size - 2) * T, T);
    memcpy((char *)self->data + (self->size - 2) * T, (char *)self->data + (self->size - 1) * T, T);
    memcpy((char *)self->data + (self->size - 1) * T, tmp, T);
}

header function void stack__rotate_(size_t T, void *tmp, struct stack(T) ref self)
{
    if (self->size < 3)
        return;
    memcpy(tmp, (char *)self->data + (self->size - 3) * T, T);
    memcpy((char *)self->data + (self->size - 3) * T, (char *)self->data + (self->size - 2) * T, T);
    memcpy((char *)self->data + (self->size - 2) * T, (char *)self->data + (self->size - 1) * T, T);
    memcpy((char *)self->data + (self->size - 1) * T, tmp, T);
}

#endif /* CBINC_STACK_H */
