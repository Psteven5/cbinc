#ifndef CBINC_DICT_H
#define CBINC_DICT_H

#include <stdint.h>

#include "slice.h"
#include "vector.h"

#define dict(T) dict

#define dict__create(T) ((struct dict(T)) {})

#define dict__insert(T, key, x, self) do {        \
    T X = (x);                                    \
    dict__insert_(sizeof(T), (key), &X, &(self)); \
} while (0)

#define dict__delete(T, key, dtor, self) do {                           \
    dict__delete_(sizeof(T), (key), (void (*)(void *))(dtor), &(self)); \
} while (0)

#define dict__search(T, key, self) ((T *)dict__search_(sizeof(T), (key), (self)))

#define dict__destroy(T, dtor, self) do {                         \
    dict__destroy_(sizeof(T), (void (*)(void *))(dtor), &(self)); \
} while (0)

#define dict__is_empty(T, self) (0 == (self).keys.size)

struct dict(T) {
    struct vector(struct slice(char)) keys;
    struct vector(T) items;
};

header function uint64_t dict__key_hash(struct slice(char) key)
{
    #define FNV_OFFSET_BASIS ((uint64_t) 0xcbf29ce484222325)
    #define FNV_PRIME        ((uint64_t) 0x100000001b3)
    
    uint64_t hash = FNV_OFFSET_BASIS;
    for (char *it = slice__begin(char, key); it < slice__end(char, key); ++it)
        hash = (hash ^ *it) * FNV_PRIME;
    return hash;

    #undef FNV_PRIME
    #undef FNV_OFFSET_BASIS
}

header function int dict__key_compare(struct slice(char) a, struct slice(char) b)
{
    if (a.size != b.size)
        return a.size - b.size;
    return memcmp(a.data, b.data, a.size);
}

header function void dict__destroy_(size_t T, void (*dtor)(void *), struct dict(T) ref self)
{
    vector__destroy_(T, dtor, &self->items);
    vector__destroy(struct slice(char), NULL, self->keys);
}

header function void dict__insert_(size_t T, struct slice(char) key, void *x, struct dict(T) ref self)
{
    if (self->keys.size + 1 >= 0.75 * self->keys.capacity) {
        size_t const capacity = self->keys.capacity < 2 * sizeof(capacity) ? 2 * sizeof(capacity) : 2 * self->keys.capacity;
        struct dict(T) new = dict__create(T);
        vector__reserve_exact(struct slice(char), capacity, new.keys);
        memset(new.keys.data, 0, capacity * sizeof(struct slice(char)));
        vector__reserve_exact_(T, capacity, &new.items);
        memset(new.items.data, 0, capacity * T);
        for (size_t i = 0; i < self->keys.capacity; ++i) {
            struct slice(char) const tmp = ((struct slice(char) *)self->keys.data)[i];
            if (NULL != tmp.data)
                dict__insert_(T, tmp, &((char *)self->items.data)[i * T], &new);
        }
        dict__destroy_(T, NULL, self);
        deref self = new;
    }
    uint64_t hash = dict__key_hash(key);
    size_t i = hash & (self->keys.capacity - 1);
    size_t const end = (hash + self->keys.capacity - 1) & (self->keys.capacity - 1);
    while (end != i) {
        struct slice(char) const tmp = ((struct slice(char) *)self->keys.data)[i];
        if (NULL == tmp.data) {
            ((struct slice(char) *)self->keys.data)[i] = key;
            memcpy(&((char *)self->items.data)[i * T], x, T);
            ++self->keys.size;
            ++self->items.size;
            return;
        }
        if (hash == dict__key_hash(tmp))
            if (0 == dict__key_compare(key, tmp))
                return;
        i = ++hash & (self->keys.capacity - 1);
    }
}

header function void dict__delete_(size_t T, struct slice(char) key, void (*dtor)(void *), struct dict(T) ref self)
{
    uint64_t hash = dict__key_hash(key);
    size_t i = hash & (self->keys.capacity - 1);
    size_t const end = (hash + self->keys.capacity - 1) & (self->keys.capacity - 1);
    for (; end != i; i = ++hash & (self->keys.capacity - 1)) {
        struct slice(char) const tmp = ((struct slice(char) *)self->keys.data)[i];
        if (NULL == tmp.data) {
            if (0 != tmp.size)
                continue;
            return;
        }
        if (hash == dict__key_hash(tmp)) {
            if (0 == dict__key_compare(key, tmp)) {
                ((struct slice(char) *)self->keys.data)[i] = slice__create(char, NULL, -1);
                if (NULL != dtor)
                    dtor(&((char *)self->items.data)[i * T]);
                --self->keys.size;
                --self->items.size;
                return;
            }
        }
    }
}

header function void *dict__search_(size_t T, struct slice(char) key, struct dict(T) self)
{
    uint64_t hash = dict__key_hash(key);
    size_t i = hash & (self.keys.capacity - 1);
    size_t const end = (hash + self.keys.capacity - 1) & (self.keys.capacity - 1);
    for (; end != i; i = ++hash & (self.keys.capacity - 1)) {
        struct slice(char) const tmp = ((struct slice(char) *)self.keys.data)[i];
        if (NULL == tmp.data) {
            if (0 != tmp.size)
                continue;
            return NULL;
        }
        if (hash == dict__key_hash(tmp))
            if (0 == dict__key_compare(key, tmp))
                return &((char *)self.items.data)[i * T];
    }
    return NULL;
}

#endif /* CBINC_DICT_H */
