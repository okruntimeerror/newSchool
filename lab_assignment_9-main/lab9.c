#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
struct RecordType
{
    int id;
    char name;
    int order;
};


struct HashType
{
    struct RecordType record;
    bool occupied;
};


int hash(int x, int hashSz)
{
    return x % hashSz;
}


void insertRecord(struct HashType *pHashArray, int hashSz, struct RecordType record)
{
    int index = hash(record.id, hashSz);

    while (pHashArray[index].occupied)
    {
        index = (index + 1) % hashSz;
    }

    pHashArray[index].record = record;
    pHashArray[index].occupied = true;
}

struct HashType *buildHashTable(struct RecordType pData[], int dataSz, int hashSz)
{
    struct HashType *pHashArray = (struct HashType *)calloc(hashSz, sizeof(struct HashType));

    for (int i = 0; i < dataSz; ++i)
    {
        insertRecord(pHashArray, hashSz, pData[i]);
    }

    return pHashArray;
}


int parseData(char *inputFileName, struct RecordType **ppData)
{
    FILE *inFile = fopen(inputFileName, "r");
    int dataSz = 0;
    int i, n;
    char c;
    struct RecordType *pRecord;
    *ppData = NULL;

    if (inFile)
    {
        fscanf(inFile, "%d\n", &dataSz);
        *ppData = (struct RecordType *)malloc(sizeof(struct RecordType) * dataSz);
        if (*ppData == NULL)
        {
            printf("Cannot allocate memory\n");
            exit(-1);
        }
        for (i = 0; i < dataSz; ++i)
        {
            pRecord = *ppData + i;
            fscanf(inFile, "%d ", &n);
            pRecord->id = n;
            fscanf(inFile, "%c ", &c);
            pRecord->name = c;
            fscanf(inFile, "%d ", &n);
            pRecord->order = n;
        }

        fclose(inFile);
    }

    return dataSz;
}


void printRecords(struct RecordType pData[], int dataSz)
{
    int i;
    printf("\nRecords:\n");
    for (i = 0; i < dataSz; ++i)
    {
        printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
    }
    printf("\n\n");
}


void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
    int i;

    printf("Hash Table:\n");
    for (i = 0; i < hashSz; ++i)
    {
        if (pHashArray[i].occupied)
        {
            printf("index %d -> %d, %c, %d\n", i, pHashArray[i].record.id, pHashArray[i].record.name, pHashArray[i].record.order);
        }
    }
    printf("\n\n");
}

int main(void)
{
    struct RecordType *pRecords;
    int recordSz = 0;

    recordSz = parseData("input.txt", &pRecords);
    printRecords(pRecords, recordSz);

    
    int hashSz = recordSz * 2;
    struct HashType *pHashTable = buildHashTable(pRecords, recordSz, hashSz);

    displayRecordsInHash(pHashTable, hashSz);

    
    free(pRecords);
    free(pHashTable);

    return 0;
}
