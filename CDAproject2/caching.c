#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

typedef struct {
    bool valid;
    bool dirty;
    int tag;
    int counter;
    char data[32];
} CacheBlock;

typedef struct {
    CacheBlock *blocks;
} CacheSet;

typedef struct {
    CacheSet *sets;
    int num_sets;
    int num_ways;
} Cache;

#define CACHE_SIZE 32
#define CACHE_LINE_SIZE 32

void initCache(Cache *cache, int num_sets, int num_ways);
bool readCache(Cache *cache, int address, char *data, bool random_replacement);
bool writeCache(Cache *cache, int address, char *data, bool random_replacement);
void updateCounter(CacheSet *set, int index, bool random_replacement);
int findLRUIndex(CacheSet *set);

int main(int argc, char **argv) {
    if (argc < 3) {
        printf("Usage: %s [trace_file] [replacement_policy]\n", argv[0]);
        printf("Replacement Policy: 0 - LRU, 1 - Random\n");
        exit(1);
    }

    srand(time(NULL));

    char *trace_file = argv[1];
    bool random_replacement = atoi(argv[2]) == 1;

    Cache cache;
    int associativity[] = {1, 2, 4, CACHE_SIZE};

    for (int i = 0; i < sizeof(associativity) / sizeof(associativity[0]); i++) {
        int num_sets = CACHE_SIZE / (associativity[i] * CACHE_LINE_SIZE);
        initCache(&cache, num_sets, associativity[i]);

        FILE *fp = fopen(trace_file, "r");
        if (fp == NULL) {
            printf("Error: could not open file %s\n", trace_file);
            exit(1);
        }

        char line[20];
        char *token;
        int address;
        char data;

        int num_accesses = 0;
        int num_hits = 0;

        // Modified loop
        while (fgets(line, sizeof(line), fp)) {
            token = strtok(line, " \n");
            address = (int)strtol(token, NULL, 16);

            // Simulate a read operation for each address
            if (readCache(&cache, address, &data, random_replacement)) {
                num_hits++;
            }
            num_accesses++;
        }

        fclose(fp);  // Close the file after the current iteration

        printf("Associativity: %d\n", associativity[i]);
        printf("Number of accesses: %d\n", num_accesses);
        printf("Number of hits: %d\n", num_hits);
        printf("Hit rate: %.2f%%\n\n", ((float)num_hits / num_accesses) * 100);

        free(cache.sets);
    }

    return 0;
}



void initCache(Cache *cache, int num_sets, int num_ways) {
    cache->sets = (CacheSet *)malloc(num_sets * sizeof(CacheSet));
    cache->num_sets = num_sets;
    cache->num_ways = num_ways;

    for (int i = 0; i < num_sets; i++) {
        cache->sets[i].blocks = (CacheBlock *)malloc(num_ways * sizeof(CacheBlock));

        for (int j = 0; j < num_ways; j++) {
            cache->sets[i].blocks[j].valid = false;
            cache->sets[i].blocks[j].counter = 0;
        }
    }
}

bool readCache(Cache *cache, int address, char *data, bool random_replacement) {
    int tag = address / (cache->num_sets * CACHE_LINE_SIZE);
    int setIndex = (address % (cache->num_sets * CACHE_LINE_SIZE)) / CACHE_LINE_SIZE;

    for (int i = 0; i < cache->num_ways; i++) {
        CacheBlock *block = &(cache->sets[setIndex].blocks[i]);
        if (block->valid && block->tag == tag) {
            updateCounter(&(cache->sets[setIndex]), i, random_replacement);
            memcpy(data, block->data, CACHE_LINE_SIZE);
            return true;
        }
    }

    return false;
}

bool writeCache(Cache *cache, int address, char *data, bool random_replacement) {
    int tag = address / (cache->num_sets * CACHE_LINE_SIZE);
    int setIndex = (address % (cache->num_sets * CACHE_LINE_SIZE)) / CACHE_LINE_SIZE;

    for (int i = 0; i < cache->num_ways; i++) {
        CacheBlock *block = &(cache->sets[setIndex].blocks[i]);
        if (block->valid && block->tag == tag) {
            updateCounter(&(cache->sets[setIndex]), i, random_replacement);
            memcpy(block->data, data, CACHE_LINE_SIZE);
            return true;
        }
    }

    int block_to_replace;
    if (random_replacement) {
        block_to_replace = rand() % cache->num_ways;
    } else {
        block_to_replace = findLRUIndex(&(cache->sets[setIndex]));
    }

    CacheBlock *block = &(cache->sets[setIndex].blocks[block_to_replace]);
    block->valid = true;
    block->tag = tag;
    updateCounter(&(cache->sets[setIndex]), block_to_replace, random_replacement);
    memcpy(block->data, data, CACHE_LINE_SIZE);
    return true;
}

void updateCounter(CacheSet *set, int index, bool random_replacement) {
    if (!random_replacement) {
        for (int i = 0; i < CACHE_SIZE / CACHE_LINE_SIZE; i++) {
            if (set->blocks[i].valid && set->blocks[i].counter < set->blocks[index].counter) {
                set->blocks[i].counter++;
            }
        }
        set->blocks[index].counter = 0;
    }
}

int findLRUIndex(CacheSet *set) {
    int lruIndex = 0;
    for (int i = 1; i < CACHE_SIZE / CACHE_LINE_SIZE; i++) {
        if (set->blocks[i].counter < set->blocks[lruIndex].counter) {
            lruIndex = i;
        }
    }
    return lruIndex;
}

