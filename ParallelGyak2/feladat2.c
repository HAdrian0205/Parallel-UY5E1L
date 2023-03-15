#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void checkIfValuesAreEqual(int array[], int size);

int main() {
    int lowerl, upperl, i, j, tempNum = 0;

    printf("Enter the number of the values: ");
    scanf("%d", &tempNum);

    const int size = tempNum;
    int array[size];

    printf("Enter the lower limit: ");
    scanf("%d", &lowerl);
    printf("Enter the upper limit: ");
    scanf("%d", &upperl);

    srand(time(NULL));

    clock_t start, end;
    double cpu_time_used;

    start = clock();

    for(i = 0; i < size; i++){
        array[i] = lowerl+(rand()%upperl);
    }

    int check = 0;

    while(1) {
        check = 0;
        for(i = 0; i < size; i++){
            for(j = i+1; j < size; j++){
                if(array[i] == array[j]){
                    array[j] = lowerl+(rand()%upperl);
                    check++;
                }
            }
        }
        if(check == 0){
            break;
        }
    }

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("The generated array:\n");
    for(i = 0; i < size; i++){
        printf("%d\n", array[i]);
    }

    printf("Calculation time %f seconds.\n", cpu_time_used);

    checkIfValuesAreEqual(array, size);

    for(i = 0; i < size; i++){
        if (rand() % 2 == 0) {
            j = rand() % size;
            array[j] = array[i];
        }
    }

    printf("\nThe generated (0.5 duplication chance) array:\n");
    for(i = 0; i < size; i++){
        printf("%d\n", array[i]);
    }

    checkIfValuesAreEqual(array, size);

    return 0;
}

void checkIfValuesAreEqual(int array[], int size){
    int i, j, check = 0;

    for(i = 0; i < size; i++){
        for(j = i+1; j < size; j++){
            if(array[i] == array[j]){
                check=1;
                break;
            }
        }
    }

    if(check == 0){
        printf("\n[CHECK]: All the values in the array are different.\n");
    } else {
        printf("\n[CHECK]: There is at least one value in the array which is duplicated.\n");
    }
}
