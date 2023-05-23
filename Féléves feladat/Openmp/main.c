#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include <sys/time.h>

double calculate_integral(double array_x[], double array_y[], int size, int mode)
{
    int n = size - 1;
    int i;
    double first_part, second_part;
    double h = (array_x[size-1] - array_x[0]) / n;
    double sum = 0.0;


    if (mode == 0){ // egyszeru teglalap
       #pragma omp parallel for reduction(+:sum)
        for (i = 0; i < size; i++) {
            sum += array_y[i];
        }

        return h * sum;
    } else if (mode == 1) { // osszetett teglalap
       #pragma omp parallel for reduction(+:sum)
        for (i = 1; i < size; i++) {
            sum += array_y[i];
        }

        return h*sum;
    } else if (mode == 2) { // osszetett trapez
       #pragma omp parallel for reduction(+:sum)
        for (i = 0; i < n; i++) {
            first_part = (array_x[i+1] - array_x[i]) / 2;
            second_part = array_y[i] + array_y[i+1];  
            sum += first_part * second_part;
        }

        return sum;
    } else {
        return -1;
    }
}

void get_size(double* a, double* b, int* size, double* h){

    double temp;
    printf("Adja meg az intervallumot: \n");
    printf("Min(a): ");
    scanf("%lf", a);
    printf("Max(b): ");
    scanf("%lf", b);

    printf("Adja meg a h-t: ");
    scanf("%lf", h);
    
    *size = 1;
    temp = *a;

    while(temp < *b){
        temp += *h;
        (*size)++;
    }

}

void get_points(double array[], double a, double b, int size, double h)
{
    int i = 0;

    #pragma omp parallel for
    for(i = 0; i < size; i++) {
        array[i] = a+i*h;
    }
}

void get_values(double array[], int size)
{
    /*printf("Adja meg a pontokhoz tartozo ertekeket:\n");

    for(int i = 0; i < size; i++) {
        printf("y[%d] = ", i);
        scanf("%lf", &array[i]);
        printf("\n");
    }*/
    srand(time(NULL));
    for(int i = 0; i < size; i++) {
        array[i] = 1 + (double)rand() / (RAND_MAX / (2 - 1 + 1) + 1);
    }
}

int main() 
{
    
    int size; // a megadott pontok, ertekek szama
    int mode; // melyik formula szerint
    int n; // részintervallumok (szakaszok) száma
    double a, b, h;

    get_size(&a, &b, &size, &h);

    double x[size];
    double y[size];

    get_points(x, a, b, size, h);

    get_values(y, size);

    printf("Valassza ki, hogy melyik szabaly szerint integralna:\n");
    printf("0 - Egyszeru teglalap, 1 - Osszetett teglalap, 2 - Osszetett trapez\n");
    scanf("%d", &mode);

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    double integral = calculate_integral(x, y, size, mode);

    gettimeofday(&end_time, NULL);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Az integral erteke: %.3f\n", integral);

    printf("Szamitasi ido: %f masodperc\n", elapsed_time);
    return 0;
}
