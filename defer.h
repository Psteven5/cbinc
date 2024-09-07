#ifndef CBINC_DEFER_H
#define CBINC_DEFER_H

#undef CAT_
#undef CAT
#undef defer

#define CAT_(a, b) a ## b
#define CAT(a, b) CAT_(a, b)

#define defer                                                                               \
    auto void CAT(DEFER_FUNCTION_, __LINE__)(int *);                                        \
    int CAT(DEFER_VAR_, __LINE__) __attribute__((cleanup(CAT(DEFER_FUNCTION_, __LINE__)))); \
    void CAT(DEFER_FUNCTION_, __LINE__)(int *)

#endif /* CBINC_DEFER_H */
