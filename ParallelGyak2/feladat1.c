#include <stdio.h>
#include <stdlib.h>

void scanValues(int array[], int size);
void printValues(int array[], int size);
int sumValues(int array[], int size);
int minValue(int array[], int size);
int maxValue(int array[], int size);

int main(){
    int i, tempNum = 0;

    printf("Enter the number of the values: ");
    scanf("%d", &tempNum);

    const int size = tempNum;
    int array[size];

    scanValues(array, size);
    printValues(array, size);

    return 0;
}

void scanValues(int array[], int size){
    int i;
    printf("Enter the values!\n");
    for(i = 0; i < size; i++) {
        printf("Value %d:\n", i+1);
        scanf("%d", &array[i]);
    }
}

void printValues(int array[], int size){
    int i;
    printf("The scanned values are:\n");
    for(i = 0; i < size-1; i++) {
        printf("%d, ", array[i]);
    }
    printf("%d\n", array[size-1]);

    int sum = sumValues(array, size);
    int min = minValue(array, size);
    int max = maxValue(array, size);

    printf("The sum: %d\n", sum);
    printf("The minimum value: %d\n", min);
    printf("The maximum value: %d\n", max);

}

int sumValues(int array[], int size){
    int i, sum = 0;

    for(i = 0; i < size; i++){
        sum += array[i];
    }

    return sum;
}

int minValue(int array[], int size){
    int i, min=array[0];

    for(i = 0; i < size; i++){
        if(array[i] < min) {
            min = array[i];
        }
    }
    return min;
}

int maxValue(int array[], int size){
    int i, max=0;

    for(i = 0; i < size; i++){
        if(array[i] > max) {
            max = array[i];
        }
    }
    return max;
}
