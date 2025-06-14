#include <stdio.h>

int main()
{
    char greetings[] = "Hello World";
    printf("%s", greetings);
    int lenght = (sizeof(greetings) / sizeof(greetings[0]) - 1);
    printf("%d", lenght);
    return 0;
}