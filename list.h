#ifndef CBINC_LIST_H
#define CBINC_LIST_H

#include <string.h>

#include <cbinc/node.h>

#define list(T) list

#define list__create(T) ((struct list(T)) {})

#define list__insert(T, pos, items, self) ({           \
    list__insert_(sizeof(T), (pos), (items), &(self)); \
})

#define list__push(T, pos, x, self) ({          \
    T X = (x);                                  \
    list__push_(sizeof(T), (pos), &X, &(self)); \
})

#define list__push_front(T, x, self) do {          \
    T X = (x);                                     \
    struct list(T) ref SELF = &(self);             \
    list__push_(sizeof(T), SELF->begin, &X, SELF); \
} while (0)

#define list__push_back(T, x, self) do {       \
    T X = (x);                                 \
    list__push_(sizeof(T), NULL, &X, &(self)); \
} while (0)

#define list__delete(T, begin, end, self) (list__delete_(sizeof(T), (begin), (end), &(self)))

#define list__pop_front(T, self) ({                                       \
    struct list(T) ref SELF = &(self);                                    \
    NULL != SELF->begin                                                   \
        ? list__delete_(sizeof(T), SELF->begin, SELF->begin->right, SELF) \
        : NULL;                                                           \
})

#define list__pop_back(T, self) ({                      \
    struct list(T) ref SELF = &(self);                  \
    list__delete_(sizeof(T), SELF->rbegin, NULL, SELF); \
})

#define list__destroy(T, dtor, self) do {                         \
    list__destroy_(sizeof(T), (void (*)(void *))(dtor), &(self)); \
} while (0)

#define list__first(T, self) node__access(T, (self).begin)

#define list__last(T, self)  node__access(T, (self).rbegin)

#define list__is_empty(T, self) (NULL == (self).begin)

struct list(T) {
    struct node(T) *begin, *rbegin;
};

header function struct node(T) *list__insert_(size_t T, struct node(T) *pos, struct list(T) items, struct list(T) ref self)
{
    if (NULL == pos) {
        if (NULL != self->rbegin) {
            items.begin->left = self->rbegin;
            self->rbegin->right = items.begin;
        } else {
            self->begin = items.begin;
        }
        self->rbegin = items.rbegin;
        return NULL;
    }
    items.rbegin->right = pos;
    if (NULL != pos->left) {
        items.begin->left = pos->left;
        pos->left->right = items.begin;
    } else {
        self->begin = items.begin;
    }
    pos->left = items.rbegin;
    return pos;
}

header function struct node(T) *list__push_(size_t T, struct node(T) *pos, void *x, struct list(T) ref self)
{
    struct node(T) *node = calloc(1, sizeof(*node) + T);
    memcpy(node->data, x, T);
    struct list(T) items = {node, node};
    return list__insert_(T, pos, items, self);
}

header function struct node(T) *list__delete_(size_t T, struct node(T) *begin, struct node(T) *end, struct list(T) ref self)
{
    if (NULL == begin || begin == end)
        return NULL;
    if (NULL != begin->left)
        begin->left->right = end;
    else
        self->begin = end;
    if (NULL != end) {
        if (NULL != end->left)
            end->left->right = NULL;
        end->left = begin->left;
    } else {
        self->rbegin = begin->left;
    }
    begin->left = NULL;
    return begin;
}

header function void list__destroy_(size_t T, void (*dtor)(void *), struct list(T) ref self)
{
    node__destroy_(dtor, self->begin);
    memset(self, 0, sizeof(deref self));
}

#endif /* CBINC_LIST_H */
