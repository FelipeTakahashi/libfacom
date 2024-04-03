#ifndef __LIBFACOM__
#define __LIBFACOM__

int getFather(int Node);

int getLeftNode(int Father);

int getRightNode(int Father);

int getMaxValue(int V[]);

void swap(int *a, int *b);

void fixDown(int V[], int Size, int Root);

void fixUp(int V[], int Node);

void build(int V[], int Size);

int insertNode(int V[], int *size, int max_size, int value);

int priorityShift(int V[], int Size, int Index, int Value);

int removeMax(int V[], int *Size);

void heapSort(int V[], int Size);

void printHeap(int V[], int Size);

void printSort(int V[], int Size);

void assertHeap(int V[], int Arr[], int Size) ;

#endif