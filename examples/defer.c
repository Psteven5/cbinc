#include <cbinc/cbinc.h>

private function int foo(void)
{
    FILE *file = fopen(__FILE__, "rb");
    if (NULL == file)
        return 1;
    defer { fclose(file); }

    fseek(file, 0, SEEK_END);
    var const size = ftell(file);
    fseek(file, 0, SEEK_SET);

    var const data = malloc(size);
    if (NULL == data)
        return 2;
    defer { free(data); }

    fread(data, size, 1, file);
    fwrite(data, size, 1, stdout);
    return 0;
}

function int main(void)
{
    defer {
        printn("");
        printn("That was the file...goodbye!!");
    }

    printn("Contents of the current file:");
    return foo();
}
