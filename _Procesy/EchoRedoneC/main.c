#include <stdio.h>

int main(int argc, char *argv[])
{
    while(!feof(stdin)) {
        fprintf(stdout, "Char: %c\n", fgetc(stdin));
        fflush(stdout);
    }

    return 0;
}
