#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "../include/heap.h"

int getFather(int Node) {
	return ((Node-1)/2);
}

int getLeftNode(int Father) {
	return (2*Father + 1);
}

int getRightNode(int Father) {
	return(2*Father+2);
}

int getMaxValue(int V[]) {
	return V[0];
}

void swap(int *a, int *b) {
	int aux = *a;
	*a = *b;
	*b = aux;
}

void fixDown(int V[], int Size, int Root) {
	int max = Root;
	int leftNode = getLeftNode(Root); //2 * Root + 1;
	int rightNode = getRightNode(Root); //2 * Root + 2;

	if(V[leftNode] > V[max] && leftNode < Size) max = leftNode;
	if(V[rightNode] > V[max] && rightNode < Size) max = rightNode;

	if(max != Root) {
		swap(&V[max], &V[Root]);
		fixDown(V, Size, max);
	}
}

void fixUp(int V[], int Node) {
	int max = getFather(Node);
	if(V[Node] > V[max]) {
		swap(&V[Node], &V[max]);
		fixUp(V, max);
	}
}

void build(int V[], int Size) {
	for(int Node = getFather(Size); Node >= 0; Node--) fixDown(V, Size, Node);
}

int insertNode(int V[], int *size, int max_size, int value) {
	int ans = EXIT_SUCCESS;
	if(*size < max_size) {
		V[*size] = value;
		*size = *size + 1;
		fixUp(V, *size-1);
	}
	else {
		ans = EXIT_FAILURE;
	}

	return ans;
}

int priorityShift(int V[], int Size, int Index, int Value) {
	if(Value > V[Index]) {
		V[Index] = Value;
		fixUp(V, Size);
	}

	if(Value < V[Index]) {
		V[Index] = Value;
		fixDown(V, Size, Index);
	}

	return EXIT_SUCCESS;
}

int removeMax(int V[], int *Size) {
	*Size = *Size -1;
	swap(&V[0], &V[*Size]);
	fixDown(V, *Size, 0); 

	return V[*Size];
}

void heapSort(int V[], int Size) {
	build(V, Size);
	for(int LastElement = Size-1; LastElement >= 1; LastElement--) {
		swap(&V[0], &V[LastElement]);
		fixDown(V, LastElement, 0);
	}
}

void printHeap(int V[], int Size) {
	printf("Max Heap: ");
	for(int i = 0; i < Size; i++) printf("%d ", V[i]);
	printf("\n");
}

void printSort(int V[], int Size) {
	printf("Sorted : ");
	for(int i = 0; i < Size; i++) printf("%d ", V[i]);
	printf("\n");
}

void assertHeap(int V[], int Arr[], int Size) {
	for(int i = 0; i < Size; i++) {
		assert(V[i] == Arr[i]);
	}
}