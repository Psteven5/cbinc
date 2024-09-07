#ifndef CBINC_UTIL_H
#define CBINC_UTIL_H

#undef private
#undef header
#undef function
#undef var
#undef restrict
#undef ref
#undef deref
#undef pun_cast

#define private static

#define header static inline

#define function

#ifdef __GNUC__
    #define var __auto_type
#endif

#define restrict __restrict

#define ref *restrict const

#define deref *

#define pun_cast(T, x) ({ \
    typeof(x) X = (x);    \
    *(T *)&X;             \
})

#endif /* CBINC_UTIL_H */
