#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/time.h>

struct ThreadData {
    double* array_x;
    double* array_y;
    double h;
    int start;
    int end;
    double result;
};

void* calculate_integral_rect(void* arg) {
    struct ThreadData* data = (struct ThreadData*)arg;
    double* array_x = data->array_x;
    double* array_y = data->array_y;
    int start = data->start;
    int end = data->end;
    int i;
    double h = data->h;
    double sum = 0.0;

    for (i = start; i < end; i++) {
        sum += array_y[i];
    }
    
    data->result = h * sum;

    pthread_exit(NULL);
}

void* calculate_integral_tr(void* arg) {
    struct ThreadData* data = (struct ThreadData*)arg;
    double* array_x = data->array_x;
    double* array_y = data->array_y;
    int start = data->start;
    int end = data->end;
    double first_part;
    double second_part;
    int i;
    double h = data->h;
    double sum = 0.0;

    for (i = start; i < end; i++) {
        first_part = (array_x[i+1] - array_x[i]) / 2;
        second_part = array_y[i] + array_y[i+1];  
        sum += first_part * second_part;
    }
    data->result = sum;

    pthread_exit(NULL);
}

void get_size(double* a, double* b, int* size, double* h) {
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

void get_points(double array[], double a, double b, int size, double h) {
    int i = 0;

    for(i = 0; i < size; i++) {
        array[i] = a+i*h;
    }
}

void get_values(double array[], int size) {
    printf("Adja meg a pontokhoz tartozo ertekeket:\n");

    for(int i = 0; i < size; i++) {
        printf("y[%d] = ", i);
        scanf("%lf", &array[i]);
        printf("\n");
    }
}

void rect_simple_threading(double* x, double* y, int size, double h){
    int num_threads = 4; 
    pthread_t threads[num_threads];
    struct ThreadData thread_data[num_threads];

    int chunk_size = size / num_threads;

    int start = 0;

    for (int i = 0; i < num_threads; i++) {
        int end = start + chunk_size;

        thread_data[i].array_x = x;
        thread_data[i].array_y = y;
        thread_data[i].h = h;
        thread_data[i].start = start;
        thread_data[i].end = end;

        pthread_create(&threads[i], NULL, calculate_integral_rect, (void*)&thread_data[i]);

        start = end;
    }

    double integral = 0.0;

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        integral += thread_data[i].result;
    }

    gettimeofday(&end_time, NULL);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Az integral erteke: %.3f\n", integral);
    printf("Szamitasi ido: %.6f masodperc\n", elapsed_time);
}

void rect_adv_threading(double* x, double* y, int size, double h){
    int num_threads = 4; 
    pthread_t threads[num_threads];
    struct ThreadData thread_data[num_threads];

    int chunk_size = size / num_threads;

    int start = 1;

    for (int i = 0; i < num_threads; i++) {
        int end = start + chunk_size;

        thread_data[i].array_x = x;
        thread_data[i].array_y = y;
        thread_data[i].h = h;
        thread_data[i].start = start;
        thread_data[i].end = end;

        pthread_create(&threads[i], NULL, calculate_integral_rect, (void*)&thread_data[i]);

        start = end;
    }

    double integral = 0.0;

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        integral += thread_data[i].result;
    }

    gettimeofday(&end_time, NULL);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Az integral erteke: %.3f\n", integral);
    printf("Szamitasi ido: %.6f masodperc\n", elapsed_time);
}

void trapeze_threading(double* x, double* y, int size, double h){
    int num_threads = 4; 
    pthread_t threads[num_threads];
    struct ThreadData thread_data[num_threads];

    int chunk_size = size / num_threads;

    int start = 0;
    
    for (int i = 0; i < num_threads; i++) {
        int end = start + chunk_size;

        thread_data[i].array_x = x;
        thread_data[i].array_y = y;
        thread_data[i].h = h;
        thread_data[i].start = start;
        thread_data[i].end = end;

        pthread_create(&threads[i], NULL, calculate_integral_tr, (void*)&thread_data[i]);

        start = end;
    }

    double integral = 0.0;

    struct timeval start_time, end_time;
    gettimeofday(&start_time, NULL);

    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL);
        integral += thread_data[i].result;
    }

    gettimeofday(&end_time, NULL);

    double elapsed_time = (end_time.tv_sec - start_time.tv_sec) + (end_time.tv_usec - start_time.tv_usec) / 1000000.0;

    printf("Az integral erteke: %.3f\n", integral);
    printf("Szamitasi ido: %.6f masodperc\n", elapsed_time);
}

int main() {
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

    if(mode == 0){
        rect_simple_threading(x, y, size, h);
    } else if (mode == 1) {
        rect_adv_threading(x, y, size, h);
    } else {
        trapeze_threading(x, y, size, h);
    }

    return 0;
}