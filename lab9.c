#include <stdio.h>
#define MAX 100

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure
struct HashType
{
    struct Node** hashArray;
    int size;
};

typedef struct Node{
    struct RecordType *dataPtr;
    struct Node *next;
}node;

// Compute the hash function
int hash(int x)
{
    x = x % MAX;

    return x;
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
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

// prints the records
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

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i=0;i<hashSz;++i)
	{
		if(pHashArray->hashArray[i] != NULL){
            printf("%d %c %d", pHashArray->hashArray[i]->dataPtr->id, pHashArray->hashArray[i]->dataPtr->name, pHashArray->hashArray[i]->dataPtr->order);
        }
	}
}

void insert(struct HashType *hashTable, struct RecordType* pRecords);

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	// Your hash implementation
    struct HashType* hashTable = (struct HashType*)malloc(1* sizeof(struct HashType));
    hashTable->size = recordSz;
    hashTable->hashArray = (node**)malloc(MAX* sizeof(node*));
    for(int i = 0; i < recordSz; i++){
        insert(hashTable, &pRecords[i]);
    }
    displayRecordsInHash(hashTable, MAX);

    // Do I need to make an array structure for the hash array or is pRecords sufficient
}

void insert(struct HashType *hashTable, struct RecordType* pRecords){
    if(pRecords == NULL){
        printf("the data is NULL");
        return;
    }

    node* newNode = (node*)malloc(sizeof(node));
    newNode->dataPtr = pRecords;

   int hashIndex = hash(pRecords->id);

    if(hashTable->hashArray[hashIndex] == NULL){
        hashTable->hashArray[hashIndex] = newNode;
    }
    else{
        newNode->next = hashTable->hashArray[hashIndex];
        hashTable->hashArray[hashIndex] = newNode;
    }

}