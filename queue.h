#ifndef CBINC_QUEUE_H
#define CBINC_QUEUE_H

#include <cbinc/list.h>

#define queue(T) list(T)

#define queue__create(T)              list__create(T)

#define queue__push(T, x, self)       list__push_back(T, (x), (self))

#define queue__pop(T, self)           list__pop_front(T, (self))

#define queue__destroy(T, dtor, self) list__destroy(T, (dtor), (self))

#define queue__front(T, self)         list__first(T, (self))

#define queue__back(T, self)          list__last(T, (self))

#define queue__is_empty(T, self)      list__is_empty(T, (self))

#endif /* CBINC_QUEUE_H */
