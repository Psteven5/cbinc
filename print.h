#ifndef CBINC_PRINT_H
#define CBINC_PRINT_H

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

#include "dependencies/map.h"

#include "util.h"

#define printfn(...) do { \
    printf(__VA_ARGS__);  \
    fputc('\n', stdout);  \
} while (0)

#define fprintfn(stream, ...) do { \
    FILE ref STREAM = (stream);    \
    fprintf(STREAM, __VA_ARGS__);  \
    fputc('\n', STREAM);           \
} while (0)

#define print_(arg) _Generic((arg)                            \
    , char *:       fprintf(STREAM, "%s",       (arg))        \
    , char const *: fprintf(STREAM, "%s",       (arg))        \
    , char:         fprintf(STREAM, "%c",       (arg))        \
    , int8_t:       fprintf(STREAM, "%" PRIi8,  (arg))        \
    , int16_t:      fprintf(STREAM, "%" PRIi16, (arg))        \
    , int32_t:      fprintf(STREAM, "%" PRIi32, (arg))        \
    , int64_t:      fprintf(STREAM, "%" PRIi64, (arg))        \
    , uint8_t:      fprintf(STREAM, "%" PRIu8,  (arg))        \
    , uint16_t:     fprintf(STREAM, "%" PRIu16, (arg))        \
    , uint32_t:     fprintf(STREAM, "%" PRIu32, (arg))        \
    , uint64_t:     fprintf(STREAM, "%" PRIu64, (arg))        \
    , float:        fprintf(STREAM, "%g",       (arg))        \
    , double:       fprintf(STREAM, "%g",       (arg))        \
    , bool:         fprintf(STREAM, (arg) ? "true" : "false") \
    , default:      fprintf(STREAM, "%p",       (arg))        \
);

#define print(...) do {       \
    FILE ref STREAM = stdout; \
    MAP(print_, __VA_ARGS__); \
} while (0)

#define fprint(stream, ...) do { \
    FILE ref STREAM = (stream);  \
    MAP(print_, __VA_ARGS__);    \
} while (0)

#define printn(...) do { \
    print(__VA_ARGS__);  \
    fputc('\n', stdout); \
} while (0)

#define fprintn(stream, ...) do { \
    FILE ref STREAM = (stream);   \
    MAP(print_, __VA_ARGS__);     \
    fputc('\n', STREAM);          \
} while (0)

#endif /* CBINC_PRINT_H */
