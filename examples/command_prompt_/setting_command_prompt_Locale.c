#include <locale.h>
#include <stdio.h>

int main()
{
    int c;
    char* l = setlocale(LC_ALL, "");
    if (l == NULL) {
        printf("Locale not set\n");
    } else {
        printf("Locale set to %s\n", l);
    }
    printf("%ls\n", L"s:\\įėšėįš");
    return 0;
}