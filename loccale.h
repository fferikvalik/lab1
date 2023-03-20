#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int input(int min, int max);
void fill_file(char* filename, int n);
void read_file(FILE* f, int n);
int deleter(char* filename, int n, FILE*f);
void swapper(FILE* f, int n, char* filename);
void task1(FILE* f, int n, char* filename);
void task2(FILE* f, int n, char* filename);
void task3(FILE* f, int n, char* filename);
void task4(FILE* f, int n, char* filename);