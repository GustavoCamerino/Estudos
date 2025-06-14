#include <stdio.h>
int main(int argc, char const *argv[])
{
    int minhaIdade = 21;
    int *ptr = &minhaIdade;
    printf("%d\n", minhaIdade);
    printf("%p\n", &minhaIdade);
    printf("%p\n", &ptr);
    return 0;
}
