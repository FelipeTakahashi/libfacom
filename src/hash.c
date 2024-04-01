#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "../include/libfacom.h"
#define SEED    0x12345678

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


int hash_insere(thash * h, void * bucket){
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



int hash_constroi(thash * h,int nbuckets, char * (*get_key)(void *) ){
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


void * hash_busca(thash h, const char * key){
    return NULL;

}

int hash_remove(thash * h, const char * key){
    return EXIT_FAILURE;

}

void hash_apaga(thash *h){
}