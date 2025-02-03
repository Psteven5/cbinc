#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "slice.h"

#define vector(T) vector

#define vector__create(T) ((struct vector(T)) {})

#define vector__reserve(T, amount, self) do {       \
    vector__reserve_(sizeof(T), (amount), &(self)); \
} while (0)

#define vector__reserve_exact(T, amount, self) do {       \
    vector__reserve_exact_(sizeof(T), (amount), &(self)); \
} while (0)

#define vector__access(T, pos, self) (slice__access(T, (pos), pun_cast(struct slice(T), (self))))

#define vector__insert(T, pos, items, self) ((T *)vector__insert_(sizeof(T), (void *)(pos), (items), &(self)))

#define vector__push_back(T, x, self) do {      \
    T X = (x);                                  \
    vector__push_back_(sizeof(T), &X, &(self)); \
} while (0)

#define vector__delete(T, pos, amount, dtor, self) ((T *)vector__delete_(sizeof(T), (void *)(pos), (amount), (void (*)(void *))(dtor), &(self)))

#define vector__pop_back(T, dtor, self) do {                         \
    vector__pop_back_(sizeof(T), (void (*)(void *))(dtor), &(self)); \
} while (0)

#define vector__destroy(T, dtor, self) do {                         \
    vector__destroy_(sizeof(T), (void (*)(void *))(dtor), &(self)); \
} while (0)

#define vector__begin(T, self) ((T *)(self).data)

#define vector__end(T, self) ({     \
    struct vector(T) SELF = (self); \
    (T *)SELF.data + SELF.size;     \
})

#define vector__rbegin(T, self) ({  \
    struct vector(T) SELF = (self); \
    (T *)SELF.data + SELF.size - 1; \
})

#define vector__rend(T, self) ((T *)(self).data - 1)

#define vector__first(T, self) (vector__access(T, 0, (self)))

#define vector__last(T, self) ({            \
    struct vector(T) SELF = (self);         \
    vector__access(T, SELF.size - 1, SELF); \
})

#define vector__is_empty(T, self) (0 == (self).size)

struct vector(T) {
    void *data;
    size_t size, capacity;
};

header function size_t cbinc__nearest2(size_t x)
{
    --x;
    for (size_t i = 1; i < sizeof(x) * 8; ++i)
        x |= x >> i;
    return ++x;
}

header function void vector__reserve_(size_t T, size_t amount, struct vector(T) ref self)
{
    if (amount > self->capacity) {
        size_t const amount2 = cbinc__nearest2(amount);
        self->data = realloc(self->data, amount2 * T);
        self->capacity = amount2;
    }
}

header function void vector__reserve_exact_(size_t T, size_t amount, struct vector(T) ref self)
{
    if (amount > self->capacity) {
        self->data = realloc(self->data, amount * T);
        self->capacity = amount;
    }
}

header function void vector__push_back_(size_t T, void *x, struct vector(T) ref self)
{
    vector__reserve_(T, self->size + 1, self);
    memcpy((char *)self->data + self->size * T, x, T);
    ++self->size;
}

header function void *vector__insert_(size_t T, char *pos, struct slice(T) items, struct vector(T) ref self)
{
    char *const data = self->data;
    if (pos > data + self->size * T)
        return data + self->size * T;
    vector__reserve_(T, self->size + items.size, self);
    pos += (char *)self->data - data;
    memmove(pos + items.size * T, pos, (char *)self->data + self->size * T - pos);
    memcpy(pos, items.data, items.size * T);
    self->size += items.size;
    return pos + items.size * T;
}

header function void vector__pop_back_(size_t T, void (*dtor)(void *), struct vector(T) ref self)
{          
    if (vector__is_empty(T, deref self))
        return;
    --self->size;
    if (NULL != dtor)
        dtor((char *)self->data + self->size * T);
}

header function void *vector__delete_(size_t T, char *pos, size_t amount, void (*dtor)(void *), struct vector(T) ref self)
{
    if (pos + amount * T > (char *)self->data + self->size * T)
        return (char *)self->data + self->size * T;
    if (NULL != dtor)
        for (char *it = pos; it < pos + amount * T; it += T)
            dtor(it);
    memmove(pos, pos + amount * T, (char *)self->data + self->size * T - (pos + amount * T));
    self->size -= amount;
    return pos < (char *)self->data + (self->size - 1) * T ? pos : (char *)self->data + (self->size - 1) * T;
}

header function void vector__destroy_(size_t T, void (*dtor)(void *), struct vector(T) ref self)
{
    if (NULL != dtor)
        for (char *it = self->data; it < (char *)self->data + self->size * T; it += T)
            dtor(it);

    free(self->data);
    memset(self, 0, sizeof(deref self));
}

#endif /* VECTOR_H */
