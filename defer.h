#ifndef CBINC_DEFER_H
#define CBINC_DEFER_H

#undef defer

#define CBINC_CAT_(a, b) a ## b
#define CBINC_CAT(a, b) CBINC_CAT_(a, b)

#define defer                                                                                           \
    auto void CBINC_CAT(DEFER_FUNCTION_, __LINE__)(int *);                                              \
    int CBINC_CAT(DEFER_VAR_, __LINE__) __attribute__((cleanup(CBINC_CAT(DEFER_FUNCTION_, __LINE__)))); \
    void CBINC_CAT(DEFER_FUNCTION_, __LINE__)(int *)

#endif /* CBINC_DEFER_H */
