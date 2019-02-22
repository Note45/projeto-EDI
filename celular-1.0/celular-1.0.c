#include <stdio.h>
#include <stdlib.h>
#include <gconio.h>
#include "prototipos.c"

int main() {
    interface();

    return 0;
}

int interface() {
    int x;
    int y;

    gotoxy(10, 10);
    printf("%c", 61);
    printf("%c", 170);
    printf("\n");
}
