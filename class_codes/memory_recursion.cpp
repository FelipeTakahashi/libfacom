#include <stdio.h>
#include <stdlib.h>

// Demonstration of local variables memory allocation

/* As rec() is a recursive function, every time it calls itself, a new local variable is created, hence,
   occupying different memory positions until the stack is complete. */

void rec(int v) {
	printf("Creating Stack : %p %d\n", (void *)&v, v);
	if (v != 0) rec(v-1);
	if (v != 0) rec(v-1); // Tree behaviour to the function
	printf("Returning Stack :  %p %d\n", (void *)&v, v); // For better visualization, comment this line
} // O(2^N) Calls and O(N) Space Complexity 

int main() { 
	int v;
	printf("Variable Address (Main) : %p\n", (void *)&v);
	// In this case, as v is a variable created in main(), its memory address stays the same, as long as it is not forcibly changed.

	v = 2;
	rec(v);

	printf("Variable Address (Main) : %p\n", (void *)&v);

	return 0;
}