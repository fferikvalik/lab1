#include "loccale.h"
#define INTMAX_MAX  999
#define INTMAX_MIN  -999
int main(int argc, char **argv) {
    if(argv[1] == NULL){
        printf("\nFilename not found\n");
        return 0;
    }
    FILE* f= fopen(argv[1],"wb+");
    int SIZE, t = 0;
    printf("Input numbers of elements: ");
    SIZE = input(1, INTMAX_MAX);
    printf("Fill file: \n");
    fill_file(argv[1], SIZE);
    while(t != 2) {
        int choose;
        printf("\nAvailable tasks:\n1.Fulfill file with odd numbers.");
        printf("\n2.Find and print the number of the element whose product with the previous element is minimal.");
        printf("\n3.Swap elements in pairs. If their number is odd, leave the last element in place.");
        printf("\n4.Remove all multiples of 5 elements.");
        printf("\nChoose task: ");
        choose = input(1, 4);
        if (choose == 1) {
            task1(f, SIZE, argv[1]);
        } else if (choose == 2) {
            task2(f, SIZE,argv[1]);
        } else {
            if (choose == 3) {
                task3(f, SIZE, argv[1]);
            } else {
                if (choose == 4) {
                    task4(f, SIZE,argv[1]);
                }
            }
        }
        printf("\n\nDo you want to choose one more task?\n1.Yes\n2.No\n");
        t = input(1,2);
    }
    fclose(f);
    return 0;
}