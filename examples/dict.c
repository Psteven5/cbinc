#include "../all"

function int main(void) {
    struct dict(int) dict = {};

    var const mario  = slice__create(char, "Mario", 5);
    var const luigi  = slice__create(char, "Luigi", 5);
    var const peach  = slice__create(char, "Peach", 5);
    var const bowser = slice__create(char, "Bowser", 5);

    dict__insert(int, mario,  1, dict);
    dict__insert(int, luigi,  2, dict);
    dict__insert(int, peach,  3, dict);
    dict__insert(int, bowser, 4, dict);

    dict__delete(int, luigi, NULL, dict);
    dict__delete(int, peach, NULL, dict);

    int const *result;

    result = dict__search(int, mario, dict);
    if (NULL != result)
        printn((char *)mario.data, ": ", *result);
    
    result = dict__search(int, luigi, dict);
    if (NULL != result)
        printn((char *)luigi.data, ": ", *result);

    result = dict__search(int, peach, dict);
    if (NULL != result)
        printn((char *)peach.data, ": ", *result);

    result = dict__search(int, bowser, dict);
    if (NULL != result)
        printn((char *)bowser.data, ": ", *result);

    dict__destroy(int, NULL, dict);
}