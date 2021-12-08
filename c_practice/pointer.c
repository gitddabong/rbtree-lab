#include <stdio.h>

int func_test(int n)
{
    printf("%d\n", n);
    return 0;
}

int main()
{
    int *numPtr;
    numPtr = 10;

    printf("%d\n", numPtr);
    printf("%p\n", numPtr);

    // int *numPtr;
    // int num1 = 10;

    // numPtr = &num1;
    // printf("%p\n", numPtr);
    // printf("%p\n", &num1);
    // printf("%ld\n", sizeof(num1));
    // printf("%ld\n", sizeof(numPtr));    // 32bit 컴퓨터에서는 4byte, 64bit 컴퓨터에서는 8byte

    // printf("%d\n", *numPtr);
    // func_test(num1);

    return 0;
}