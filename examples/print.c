#include <time.h>

#include "../all"

function int main(void) {
    printn("GUESS THE NUMBER!!!");

    var const MINIMUM = 1;
    var const MAXIMUM = 10;
    
    srand(time(NULL));
    for (;;) {
        var const random = rand() % (MAXIMUM + 1 - MINIMUM) + MINIMUM;

        int number;

        print("> ");
        fflush(stdin);
        if (1 != scanf("%d", &number)) {
            fprintn(stderr, "error: not a number");
            continue;
        }
        
        if (number < MINIMUM || MAXIMUM < number) {
            fprintn(stderr, "error: ", number, " is not between ", MINIMUM, " and ", MAXIMUM, " (inclusive)");
            continue;
        }

        print("you guessed ", number);

        if (random == number)
            printn("... and that's correct!");
        else
            printn("... but the number was ", random);
        
        printn("");
    }
}