#include <stdlib.h>


typedef struct
{
    int array[100];
    int len;
} vector;


void sum_and_product(int a, int *sum, int *product) {
    *sum += a;
    *product *= a;
}

void option1()
{
    int element, sum=0, product=1;
                while(element!= 0)
                    {
                        scanf(element);
                        sum_and_product(element, &sum, &product);
                    }
                prinf(sum, " ", product);
}
void option2()
{
    int longest=0; 
    int current_element=0;
    int beginning_of_longest=0;

    vector array;
    scanf(array.len);
    for (int i=1; i<=array.len ; i++)
        scanf(array.array[i])
        if()
        if(array.array[i]==array.array[i-1]) 
            


    
}
void menu()
{

    int option;
    while(1)
    {
        printf("1. Sum and prod of all numberes you input");
        printf("2. Longest equal continuous subsequence");
         int option;
        scanf(option);
        if (option==1)
            option1();
        else if(option==2)
            option2();
    }
}

int main()
{
    menu();
    return 0;
}