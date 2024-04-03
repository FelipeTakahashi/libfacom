#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

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

void test_pai(){

    int r;

    r = getFather(6);
    assert(r == 2);
    r = getFather(5);
    assert(r == 2);
    r = getFather(0);
    assert(r == 0);
}

void test_filho_esq(){
    int r;

    r = getLeftNode(0);
    assert(r==1);
    r = getLeftNode(1);
    assert(r==3);
    r = getLeftNode(2);
    assert(r==5);
}

void test_filho_dir(){
    int r;

    r = getRightNode(0);
    assert(r==2);
    r = getRightNode(1);
    assert(r==4);
    r = getRightNode(2);
    assert(r==6);
}

void test_desce(){
    int entrada[] = {1,5,3,4,10,2,0};
    int saida[]   = {5,10,3,4,1,2,0};

    int i;
    int max_size = sizeof(entrada)/sizeof(entrada[0]);
  
    fixDown(entrada,max_size,0);

    for (i=0;i<max_size;i++){
        assert(entrada[i]==saida[i]);
    }
}

void test_constroi_heap(){
    int entrada[] = {1,50,20,62,60,25,30};
    int saida[]   = {62,60,30,50,1,25,20};

    int i;
    int max_size = sizeof(entrada)/sizeof(entrada[0]);
  
    build(entrada,max_size);
   
    for (i=0;i<max_size;i++){
        assert(entrada[i]==saida[i]);
    }

}

void test_sobe() {
	int entrada[] = {62, 60, 30, 50, 100, 25, 20};
	int saida[] = {100, 62, 30, 50, 60, 25, 20};

	int i;
	int max_size = sizeof(entrada)/sizeof(entrada[0]);

	fixUp(entrada, 4);

	for(i = 0; i < max_size; i++) assert(entrada[i] == saida[i]);
}

void test_acessa_max(){
    int v[] = {100,62,30,50,60,25,20};
    assert(getMaxValue(v) == 100);
}

void test_extrai_max(){
    int entrada[] = {100,62,30,50,60,25,20};
    int saida1[]   = {62,60,30,50,20,25};
    int saida2[]   = {60,50,30,25,20};

    int i;
    int max_size = sizeof(entrada)/sizeof(entrada[0]);

    assert(removeMax(entrada,&max_size)==100);
    assert(max_size == 6);
    
    for (i=0;i<max_size;i++){
        assert(entrada[i]==saida1[i]);
    }

    assert(removeMax(entrada,&max_size)==62);
    assert(max_size == 5);
    
    for (i=0;i<max_size;i++){
        assert(entrada[i]==saida2[i]);
    }
}

void test_insere_elemento(){
    int max_size = 10;
    int entrada[10] = {100,62,30,50,60,25,20};
    int saida1[]   = {100,70,30,62,60,25,20,50};
    int saida2[]   = {150,100,30,70,60,25,20,50,62};;

    int i;
    int tam = 7;

    assert(insertNode(entrada,&tam,max_size,70)==EXIT_SUCCESS);
    assert(tam == 8);
    
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida1[i]);
    }

    assert(insertNode(entrada,&tam,max_size,150)==EXIT_SUCCESS);
    assert(tam == 9);
    
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida2[i]);
    }
}

void test_altera_prioridade(){
    int max_size = 10;
    int entrada[10] = {100,62,30,50,60,25,20};
    int saida1[]    = {105,100,30,50,60,25,20};
    int saida2[]    = {100,60,30,50,1,25,20};
    int i;
    int tam = 7 ;
   
    assert(priorityShift(entrada,tam,1,105)==EXIT_SUCCESS);
    
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida1[i]);
    }
    
    assert(priorityShift(entrada,tam,0,1)==EXIT_SUCCESS);
    
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida2[i]);
    }
}
void test_heapsort(){
    int entrada[]   = {100,62,30,50,60,25,20};
    int saida[]     = {20 ,25,30,50,60,62,100};
    int tam = sizeof(entrada)/sizeof(entrada[0]);
    int i;

    heapSort(entrada,tam);
    for (i=0;i<tam;i++){
        assert(entrada[i]==saida[i]);
    }
}

int main() {
	int DownSample[3] = {1, 2, 3};
	fixDown(DownSample, 3, 0);
	printHeap(DownSample, 3);

	int UpSample[3] = {1, 2, 3};
	fixUp(UpSample, 2);
	printHeap(UpSample, 3);

	int BasicSample[5] = {1, 5, 2, 3, 4};
	build(BasicSample, 5);
	printHeap(BasicSample, 5);
	
	int leftIndex = getLeftNode(0);
	int rightIndex = getRightNode(0);
	int fatherIndex = getFather(1);
	printf("    Father: %d \n    Left Node: %d \n    Right Node: %d \n", BasicSample[fatherIndex], BasicSample[leftIndex], BasicSample[rightIndex]);

	test_pai();
	test_filho_esq();
	test_filho_dir();
	test_desce();
	test_sobe();
	test_constroi_heap();
	test_acessa_max();
	test_acessa_max();
	test_extrai_max();
	test_insere_elemento();
	test_heapsort();

	return EXIT_SUCCESS;
}