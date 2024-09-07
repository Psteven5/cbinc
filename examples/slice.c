#include "../all"

private function void foo(struct slice(int) slice)
{
    int const *result;

    result = slice__access(int, 41, slice);
    if (NULL != result)
        printn(*result);

    result = slice__access(int, 42, slice);
    if (NULL != result)
        printn(*result);

    for (var it = slice__begin(int, slice); it < slice__end(int, slice); ++it)
        print(*it, (char) ' ');
    
    if (!slice__is_empty(int, slice))
        printn("");
}

function int main(void)
{
    int numbers[42];
    for (int i = 0; i < sizeof(numbers) / sizeof(*numbers); ++i)
        numbers[i] = i + 1;
    
    var const slice = slice__create(int, numbers, sizeof(numbers) / sizeof(*numbers));
    foo(slice);
}
