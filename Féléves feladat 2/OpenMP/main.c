#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>
#include <sys/time.h>

double integrableFunction(double x, int func)
{
    if(func == 0){
        return sin(x);
    } else if(func == 1) {
        return cos(x);
    } else if(func == 2) {
        return exp(x);
    } else if(func == 3) {
        return sqrt(x);
    } else {
        return log(x);
    }
}

double calculate_integral(double array_x[], double h, int size, int mode, int func)
{
    int n = size - 1;
    int i;
    double sum = 0.0;

    int num_threads = 4;
    omp_set_num_threads(num_threads);

    if (mode == 0){ // egyszeru teglalap
        #pragma omp parallel for reduction(+:sum)
        for (i = 0; i < n; i++) {
            sum += integrableFunction(array_x[i], func);
        }
        return h * sum;
        
    } else if (mode == 1) { // osszetett teglalap
        #pragma omp parallel for reduction(+:sum)
        for (i = 1; i < size; i++) {
            sum += integrableFunction(array_x[i], func);
        }
        return h*sum;

    } else if (mode == 2) { // osszetett trapez
        #pragma omp parallel for reduction(+:sum)
        for (i = 0; i < n; i++) {
            sum += ((array_x[i+1] - array_x[i]) / 2) * (integrableFunction(array_x[i], func) + integrableFunction(array_x[i+1], func));
        }
        return sum;
    } else {
        return -1;
    }
}

void get_size(double* a, double* b, int* size, double* h)
{
    printf("Adja meg az intervallumot: \n");
    printf("Min(a): ");
    scanf("%lf", a);
    printf("Max(b): ");
    scanf("%lf", b);

    printf("Adja meg az n-et: ");
    scanf("%d", size);
    
    *h = (*b-*a) / *size;
}

void get_points(double array[], double a, double b, int size, double h)
{
    int i = 0;

    for(i = 0; i < size; i++) {
        array[i] = a+i*h;
    }
}

int main() 
{
    
    int size; // a megadott pontok, ertekek szama
    int mode, func; // melyik formula szerint, melyik függvény
    double a, b, h;

    get_size(&a, &b, &size, &h);

    double x[size];

    get_points(x, a, b, size, h);

    printf("Valassza ki, hogy melyik szabaly szerint integralna:\n");
    printf("0 - Egyszeru teglalap, 1 - Osszetett teglalap, 2 - Osszetett trapez\n");
    scanf("%d", &mode);
    printf("Valassza ki, hogy melyik fuggvenyt integralna:\n");
    printf("0 - sin, 1 - cos, 2 - exp, 3 - sqrt, 4 - log\n");
    scanf("%d", &func);

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    double integral = calculate_integral(x, h, size, mode, func);

    gettimeofday(&end_time, NULL);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Az integral erteke: %.3f\n", integral);
    printf("Szamitasi ido: %.6f masodperc\n", elapsed_time);
    return 0;
}