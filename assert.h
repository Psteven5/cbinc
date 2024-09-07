#ifndef CBINC_ASSERT_H
#define CBINC_ASSERT_H

#include <stdio.h>

#include "util.h"

#undef STR_
#undef STR
#undef assert

#define STR_(x) # x
#define STR(x) STR_(x)

#define assert(x) while (!(x)) {         \
    assert_(__FILE__, __LINE__, STR(x)); \
    __builtin_unreachable();             \
}

header function void assert_(char const *file, int line, char const *assertion)
{
    #ifndef NDEBUG
        fprintf(stderr, "%s:%i assertion failed: '%s'\n", file, line, assertion);
    #endif
}

#endif /* CBINC_ASSERT_H */
