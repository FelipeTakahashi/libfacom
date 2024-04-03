#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define SEED 0x12345678

typedef struct {
     uintptr_t * table;
     int size;
     int max;
     uintptr_t deleted;
     char * (*get_key)(void *);
}hash_t;

uint32_t hashf(const char* str, uint32_t h){
    /* One-byte-at-a-time Murmur hash 
    Source: https://github.com/aappleby/smhasher/blob/master/src/Hashes.cpp */
    for (; *str; ++str) {
        h ^= *str;
        h *= 0x5bd1e995;
        h ^= h >> 15;
    }
    return h;
}

int hash_insert(hash_t * h, void * bucket){
    uint32_t hash = hashf(h->get_key(bucket), SEED);
    int pos = hash % (h->max);
    int tableSize = h->table + h->size;
    
    if(h->max == h->size+1) { 
        free(bucket);
        return EXIT_FAILURE;
    }else {
        while(h->table[pos] != NULL) {
            if(h->table[pos] == h->deleted) break;
            pos = (pos+1)%h->max;
        }
        h->table[pos] = (uintptr_t)bucket;
        h->size += 1;
    }

    return EXIT_SUCCESS;

}

int hash_init(hash_t * h,int nbuckets, char * (*get_key)(void *) ){
    h->table = calloc(nbuckets+1, sizeof(void*));
    if(h->table == NULL) {
        return EXIT_FAILURE;
    }

    h->max = nbuckets + 1;
    h->size = 0;
    h->deleted = (uintptr_t)&(h->size); 
    h->get_key = get_key;

    return EXIT_SUCCESS;

}

void * hash_search(hash_t h, const char * key){
    return NULL;

}

int hash_remove(hash_t * h, const char * key){
    int pos;
    for(pos = 0; pos < h->max; pos++) {
        if(h->table[pos] != 0) {
            if(h->table[pos] != h->deleted) {
                free((void*)h->table[pos]);
            }
        }
    }
    free(h->table);
}

void hash_delete(hash_t *h){
}

typedef struct{
    char name[30];
    char cpf[11];
}student_t;

char * get_key(void * reg){
    return (*((student_t *)reg)).name;
}


void * student_alloc(char * name, char * cpf){
    student_t * student = malloc(sizeof(student_t));
    strcpy(student->name,name);
    strcpy(student->cpf,cpf);
    return student;
}



void test_insert(){
    hash_t h;
    int nbuckets = 10;

    hash_init(&h,nbuckets,get_key);

    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_FAILURE);

    hash_apaga(&h);
}
void test_search(){
    hash_t h;
    int nbuckets = 10;
    student_t * student;

    hash_init(&h,nbuckets,get_key);

    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("takashi","1123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("matsubara","2123456789"))==EXIT_SUCCESS);

    student = hash_search(h,"edson");
    assert(student->cpf[0]=='0');
    student = hash_search(h,"takashi");
    assert(student->cpf[0]=='1');
    student = hash_search(h,"matsubara");
    assert(student->cpf[0]=='2');
    student = hash_search(h,"patricia");
    assert(student == NULL);

    hash_apaga(&h);
}

void test_remove(){
    hash_t h;
    int nbuckets = 10;
    student_t * student;
    hash_init(&h,nbuckets,get_key);
    assert(hash_insert(&h,student_alloc("edson","0123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("takashi","1123456789"))==EXIT_SUCCESS);
    assert(hash_insert(&h,student_alloc("matsubara","2123456789"))==EXIT_SUCCESS);

    student = hash_search(h,"edson");
    assert(student->cpf[0]=='0');
    student = hash_search(h,"takashi");
    assert(student->cpf[0]=='1');
    student = hash_search(h,"matsubara");
    assert(student->cpf[0]=='2');
    student = hash_search(h,"patricia");
    assert(student == NULL);

    assert(h.size == 3);
    assert(hash_remove(&h,"edson")==EXIT_SUCCESS);
    student = hash_search(h,"edson");
    assert(student == NULL);
    assert(h.size == 2);

    assert(hash_remove(&h,"edson")==EXIT_FAILURE);

    student = hash_search(h,"matsubara");
    assert(student->cpf[0]=='2');


    hash_delete(&h);

}

int main(int argc, char* argv[]){
    test_insert();
    test_search();
    test_remove();
    return 0;
}