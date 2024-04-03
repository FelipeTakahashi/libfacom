#include <stdio.h>
#include <stdlib.h> 

// Demonstration of memory stack behaviour and changing values through memory

int main() {
    int i[10];
    int *p;
    int b;

    p = i;

    b = 7;
    printf("b : %d\n", b);

    // Due to stack behaviour, the variables are stored in a downward motion.
    printf("i address : %p\n", &i);
    printf("p address : %p\n", &p);
    printf("b address : %p\n", &b);

    *(i - (&i[0] - &b)) = 6; // manipulating b through its memory adress  
    printf("b : %d\n", b);

    p = i - (&i[0] - &b); // p is equal to the memory address of b
    *p = 5; // manipulating b through pointer p

    printf("b : %d\n", b);

    return EXIT_SUCCESS;
}