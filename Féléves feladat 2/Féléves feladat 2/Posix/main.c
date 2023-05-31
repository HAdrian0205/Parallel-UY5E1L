#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>
#include <sys/time.h>

struct ThreadData {
    double* array_x;
    double h;
    int start;
    int end;
    int func;
    double* sum_array;
};

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

void* calculate_integral_rect(void* arg) {
    struct ThreadData* data = (struct ThreadData*)arg;
    double* array_x = data->array_x;
    int start = data->start;
    int end = data->end;
    int i;
    int func = data->func;
    double h = data->h;

    for (i = start; i < end; i++) {
        data->sum_array[i] += integrableFunction(array_x[i], func);
    }

    pthread_exit(NULL);
}

void* calculate_integral_tr(void* arg) {
    struct ThreadData* data = (struct ThreadData*)arg;
    double* array_x = data->array_x;
    int start = data->start;
    int end = data->end;
    int i;
    int func = data->func;
    double h = data->h;

    for (i = start; i < end; i++) {
        data->sum_array[i] += ((array_x[i+1] - array_x[i]) / 2) * (integrableFunction(array_x[i], func) + integrableFunction(array_x[i+1], func));
    }

    pthread_exit(NULL);
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
    
    *h = (*b-*a) / (*size-1);
}

void get_points(double array[], double a, double b, int size, double h)
{
    int i = 0;

    for(i = 0; i < size; i++) {
        array[i] = a+i*h;
    }
}

double calculate_sum(double* sum_array, int size, int mode, double h) {
    double sum = 0.0;
    int i;
    
    if(mode == 0){
        for (i = 0; i < size-1; i++) {
            sum += sum_array[i];
        }

        return h*sum;
    } else if (mode == 1) {
        for (i = 1; i < size; i++) {
            sum += sum_array[i];
        }

        return h*sum;
    } else {
        for (i = 0; i < size-1; i++) {
            sum += sum_array[i];
        }
        return sum;
    }

    
}

void threading(double* x, int size, int func, double h, int mode) {
    int num_threads = 20;
    pthread_t threads[num_threads];
    struct ThreadData thread_data[num_threads];

    double sum_array[size];

    for (int i = 0; i < size; i++) {
        sum_array[i] = 0.0;
    }

    int chunk_size = size / num_threads;
    int start;

    if (mode == 1) {
        start = 1;
    } else {
        start = 0;
    }

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    if (mode == 0 || mode == 1) {
        for (int i = 0; i < num_threads; i++) {
            int end = start + chunk_size;

            thread_data[i].array_x = x;
            thread_data[i].sum_array = sum_array;
            thread_data[i].h = h;
            thread_data[i].start = start;
            thread_data[i].end = end;
            thread_data[i].func = func;

            pthread_create(&threads[i], NULL, calculate_integral_rect, (void*)&thread_data[i]);

            start = end;
        }
    } else {
        for (int i = 0; i < num_threads; i++) {
            int end = start + chunk_size;

            thread_data[i].array_x = x;
            thread_data[i].sum_array = sum_array;
            thread_data[i].h = h;
            thread_data[i].start = start;
            thread_data[i].end = end;
            thread_data[i].func = func;

            pthread_create(&threads[i], NULL, calculate_integral_tr, (void*)&thread_data[i]);

            start = end;
        }
    }

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
    }

    double integral = calculate_sum(sum_array, size, mode, h);

    gettimeofday(&end_time, NULL);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Az integral erteke: %.6f\n", integral);
    printf("Szamitasi ido: %.6f masodperc\n", elapsed_time);

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
    if((func == 3 || func == 4) && (a < 0 || b < 0)) {
        printf("Negativ szamot tartalmazo intervallum eseten nem hasznalhatod ezt a fuggvenyt!");
        return -1;
    }
    scanf("%d", &func);

    threading(x, size, func, h, mode);
    return 0;
}
