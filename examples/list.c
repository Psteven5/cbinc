#include <stdnoreturn.h>

#include "../list.h"
#include "../print.h"

noreturn function int main(void)
{
    struct list(char) list = {};

    list__push_back(char, 'A', list);
    list__push_back(char, 'B', list);
    list__push_back(char, 'C', list);
    list__push_back(char, 'D', list);

    list__pop_front(char, list);
    list__pop_back(char,  list);

    list__insert(char, NULL, list, list);

    for (var it = list.begin; NULL != it; it = it->right)
        print(*(char *)it->data, (char) ' ');
}
