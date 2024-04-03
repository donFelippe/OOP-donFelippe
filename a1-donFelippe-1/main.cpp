    #include <stdio.h>
#include <cmath>

/*
     * a. Read a sequence of natural numbers (sequence ended by 0) and determine the number of
     * 0 digits of the product of the read numbers.
    b. Given a vector of numbers, find the longest contiguous subsequence such that the sum of any
     two consecutive elements is a prime number.
     *
     */
int number_of_2_in_prime_decomposition(int number) {
    int number_of_2 = 0;
    while (number % 2 == 0) {
        number /= 2;
        number_of_2 += 1;
    }
    return number_of_2;

}

int number_of_5_in_prime_decomposition(int number) {
    int number_of_5 = 0;
    while (number % 5 == 0) {
        number /= 5;
        number_of_5 += 1;
    }
    return number_of_5;

}

int problem_1() {
    int number_of_5_in_decomposition = 0, number_of_2_in_decomposition = 0;
    int reader = 1;
    while (reader != 0) {

        scanf("%d", &reader);
        if (reader != 0) {
            number_of_5_in_decomposition += number_of_5_in_prime_decomposition(reader);
            number_of_2_in_decomposition += number_of_2_in_prime_decomposition(reader);
        }
    }
    if (number_of_2_in_decomposition < number_of_5_in_decomposition)
        return number_of_2_in_decomposition;
    return number_of_5_in_decomposition;
}

int is_prime(int n) {
    if (n<1) return 0;
    for (int i = 2; i <= sqrt(n); i++)
        if (n % i == 0) return 0;
    return 1;
}

int problem_2() {
    int reader, len = 0;
    int array[100];
    while (true) {
        scanf("%d", &array[len]);
        if (array[len] == 0) break;
        len++;
    } // new readin f
    int beginning = 0, finish = 0, beginning_ultimate, finish_ultimate;
    for (int i = 1; i <= len; i++) {
        if (is_prime(array[i - 1] + array[i]))
        {
                finish +=1;
        }
        else
        {
            if (finish - beginning > finish_ultimate - beginning_ultimate)
            {
                beginning_ultimate = beginning;
                finish_ultimate = finish;
            }
            beginning = finish;
        }

    }
    return finish_ultimate-beginning_ultimate+1;
}

void console() {
    printf("problem statement 6. possible commands: \n 1 - number of 0 digits in product \n 2 - longest contiguous subsequence, sum of every consecutive elements is prime \n 3 - exit program");
    int problem_statement;
    scanf("%d", &problem_statement);
    while (problem_statement != 3)
    {
        if (problem_statement == 1)
            printf("number of 0's in the final product: %d", problem_1());
         else
        {
            if (problem_statement == 2)
                printf("%d",problem_2());
            else printf("%d", "No such problem implemented");

        }
        scanf("%d", problem_statement);
    }
}

int main() {
    console();
    return 0;
}