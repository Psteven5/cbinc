#include <time.h>

#include "../all"

typedef __bf16 bfloat16_t;

private function void fill(struct vector(bfloat16_t) ref v) {
    for (size_t _ = v->capacity; 0 != _; --_)
        vector__push_back(bfloat16_t, (double) rand() / RAND_MAX - 0.5, deref v);
}

private function void show(struct vector(bfloat16_t) v) {
    for (var it = vector__begin(bfloat16_t, v); it < vector__end(bfloat16_t, v); ++it)
        print((double) *it, (char) ' ');
    printn((char) '\n');
}

function int main(void) {
    srand(time(NULL));

    struct vector(bfloat16_t) w0 = {}, w1 = {}, w2 = {};

    vector__reserve_exact(bfloat16_t, 100, w0);
    vector__reserve_exact(bfloat16_t, 100, w1);
    vector__reserve_exact(bfloat16_t, 10,  w2);

    fill(&w0);
    fill(&w1);
    fill(&w2);

    printn("w0:");
    show(w0);

    printn("w1:");
    show(w1);

    printn("w2:");
    show(w2);

    vector__destroy(bfloat16_t, NULL, w2);
    vector__destroy(bfloat16_t, NULL, w1);
    vector__destroy(bfloat16_t, NULL, w0);
}