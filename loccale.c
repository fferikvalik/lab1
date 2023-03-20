//
// Created by Valentin Gouriev on 20.02.23.
//
#include "loccale.h"
#define INTMAX_MAX  9999
#define INTMAX_MIN  -9999
#define MAX_LEN 100
int input(int min, int max){
    int x;
    while (scanf("%d", &x) != 1 || x < min || x > max || x % 1 != 0 || getchar() != '\n') {
        printf("Error. Try again: ");
        rewind(stdin);
    }
    return x;
}

void fill_file(char* filename, int n){
    int* arr = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; ++i) {
        printf("Input %d element: ", i + 1);
        arr[i] = input(INTMAX_MIN, INTMAX_MAX);
    }
    FILE* f;
    f=fopen(filename, "wb+");
    fwrite(arr, sizeof(int), n, f);
    fflush(f);
    fclose(f);
}

void read_file(FILE* f, int n){
    int num;
    fseek(f, 0, SEEK_END);
    n=(ftell(f))/4;
    rewind(f);
    for (int i = 0; i < n; ++i) {
        fread(&num, sizeof(int), 1,f);
        printf("%d ", num);
    }
    rewind(f);
}


int deleter(char* filename, int n, FILE* f) {
    fpos_t pos;
    int num, tmp, counter = 0;
    freopen(filename, "rb+",f);

    int size = sizeof(int);

    fseek(f, 0, SEEK_END);
    pos = ftell(f);
    int len = pos / size;
    rewind(f);
    for (int i = 0; i < len; ++i) {
        fseek(f, i * size, SEEK_SET);
        fread(&num, size, 1, f);
        if (num % 5 == 0) {
            counter++;
        }
        for (int i = 0; i < len; i++) {
            for (int j = 0; j <= len - 2; ++j) {
                fseek(f, j * size, SEEK_SET);
                fread(&num, size, 1, f);
                fread(&tmp, size, 1, f);
                if (num % 5 == 0) {
                    fseek(f, j * size, SEEK_SET);
                    fwrite(&tmp, size, 1, f);
                    fwrite(&num, size, 1, f);
                }
            }
        }
    }
    n=len-counter;
    int *arr;
    arr= malloc(n*sizeof(int));
    for (int i = 0; i < n; ++i) {
        fseek(f, i * size, SEEK_SET);
        fread(&num, size, 1, f);
        arr[i]=num;
    }
    freopen(filename,"w+b",f);
    //printf("\n\nTest: ");
    for (int i = 0; i < n; ++i) {
        fwrite(&arr[i], size, 1, f);
    }
    fclose(f);
    return n;
}

void task1(FILE* f, int n, char* filename) {
    freopen(filename,"r+b",f);
    printf("\nYour File: ");
    read_file(f, n);
}

void task2(FILE* f, int n, char* filename){
    freopen(filename, "r+b",f);
    printf("\nFile state: ");
    read_file(f, n);
    fseek(f, 0, SEEK_END);
    n=(ftell(f))/4;
    int  i, min_index = 1;
    int arr[MAX_LEN];
    rewind(f);
    for (int j = 0; j < n; ++j) {
        fread(&arr[j],sizeof(int),1,f);
    }
    int min_product = arr[0] * arr[1];
        for (i = 2; i < n; i++) {
            int product = arr[i] * arr[i-1];
            if (product < min_product) {
                min_product = product;
                min_index = i;
            }
        }

        printf("Номер элемента, произведение которого с предыдущим элементом минимально: %d\n", ++min_index);
    fclose(f);
}

void swapper(FILE* f, int n, char* filename){
    freopen(filename,"r+b",f);
    int m, num1,num2;
    size_t s= sizeof(int);
    m=n/2;
    for (int i = 0; i < m; ++i) {
        fread(&num1,s,1,f);
        fread(&num2,s,1,f);
        fseek(f,-(2*s),SEEK_CUR);
        fwrite(&num2,s,1,f);
        fwrite(&num1,s,1,f);
    }
    fclose(f);
}

void task3(FILE* f, int n, char* filename) {
    freopen(filename, "r+b", f);
    printf("\nFile state: ");
    read_file(f, n);
    fseek(f, 0, SEEK_END);
    n=(ftell(f))/4;
    swapper(f,n, filename);
    freopen(filename,"r+b", f);
    printf("\n\nCorrected file: ");
    read_file(f, n);
    fclose(f);
}

void task4(FILE* f, int n, char* filename) {
    freopen(filename, "r+b", f);
    printf("\nCurrant file: ");
    read_file(f,n);
    printf("\nSorted file: ");
    deleter(filename,n,f);
    freopen(filename, "r+b", f);
    read_file(f, n);
}