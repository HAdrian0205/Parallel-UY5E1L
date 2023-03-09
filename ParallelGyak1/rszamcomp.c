#include <Windows.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    time_t t1;
    srand ( (unsigned) time (&t1));

    int i, n, a, b;

    printf("Adja meg a generalando szamok szamat!\n");
    scanf("%d", &n);

    printf("Adja meg az also hatart!\n");
    scanf("%d", &a);
    printf("Adja meg a felso hatart!\n");
    scanf("%d", &b);

    printf("Szamok generalasa:\n");
    sleep(2);

    for(i = 0; i < n; i++) {
        printf("%d\n", a+(rand()%b));
    }

    FILE *fp;
    fp = fopen("rszamok.txt", "w");

    for(i = 0; i < n; i++) {
        fprintf(fp, "%d\n", a+(rand()%b));
    }
    fclose(fp);
    return 0;
}
