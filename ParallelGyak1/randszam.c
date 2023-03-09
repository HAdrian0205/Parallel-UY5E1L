#include <Windows.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    time_t t1;
    srand ( (unsigned) time (&t1));

    printf("Szam generalasa 2mp mulva!\n");

    sleep(2);

    printf("A generalt szam: %d", rand()%50);

    return 0;
}
