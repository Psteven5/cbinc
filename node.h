#ifndef CBINC_NODE_H
#define CBINC_NODE_H

#include <stdlib.h>

#include "util.h"

#define node(T) node

#define node__create(T) ((struct node(T) *)calloc(1, sizeof(struct node(T) + T)))

#define node__access(T, self) ((T *)node__access_((self)))

#define node__destroy(T, dtor, self) do {             \
    node__destroy_((void (*)(void *))(dtor), (self)); \
} while (0)

struct node(T) {
    struct node(T) *right, *left;
    char data[];
};

header function void *node__access_(struct node(T) *self)
{
    if (NULL == self)
        return NULL;
    return self->data;
}

header function void node__destroy_(void (*dtor)(void *), struct node(T) *self)
{
    for (; NULL != self;) {
        struct node(T) *tmp = self->right;
        if (NULL != dtor)
            dtor(self->data);
        free(self);
        self = tmp;
    }
}

#endif /* CBINC_NODE_H */
