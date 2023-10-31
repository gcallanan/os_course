#include <stdio.h>

int multiplyByTwo(int input);

int main() {
    int i = 10;
    int result = multiplyByTwo(i);
    printf("Result: %i\n", result);
    return 0;
}

int multiplyByTwo(int input){
    int output = input * 2;
    return output;
}