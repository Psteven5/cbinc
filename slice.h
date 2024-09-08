#ifndef CBINC_SLICE_H
#define CBINC_SLICE_H

#include <stddef.h>

#include <cbinc/util.h>

#define slice(T) slice

#define slice__create(T, data, size) ((struct slice(T)) {(data), (size)})

#define slice__access(T, pos, self) ((T *)slice__access_(sizeof(T), (pos), (self)))

#define slice__begin(T, self) ((T *)(self).data)

#define slice__end(T, self) ({     \
    struct slice(T) SELF = (self); \
    (T *)SELF.data + SELF.size;    \
})

#define slice__rbegin(T, self) ({   \
    struct slice(T) SELF = (self);  \
    (T *)SELF.data + SELF.size - 1; \
})

#define slice__rend(T, self) ((T *)(self).data - 1)

#define slice__first(T, self) ({   \
    struct slice(T) SELF = (self); \
    slice__access(T, 0, SELF);     \
})

#define slice__last(T, self) ({            \
    struct slice(T) SELF = (self);         \
    slice__access(T, SELF.size - 1, SELF); \
})

#define slice__is_empty(T, self) (0 == (self).size)

struct slice(T) {
    void *data;
    size_t size;
};

header function void *slice__access_(size_t T, size_t pos, struct slice(T) self)
{
    if (pos >= self.size)
        return NULL;
    return &((char *)self.data)[pos * T];
}

#endif /* CBINC_SLICE_H */
