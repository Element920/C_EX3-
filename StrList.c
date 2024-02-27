// StrList.c

#include "StrList.h"
#include <stdio.h>
#include <string.h>

int myCompare(const void* a, const void* b) 
{ 
    return strcmp(*(const char**)a, *(const char**)b); 
} 

StrList* StrList_alloc() {
    StrList* newList = (StrList*)malloc(sizeof(struct _StrList));
    newList->data = NULL;
    newList->size = 0;
    return newList;
}

void StrList_free(StrList* StrList) {
    if (StrList == NULL) return;
    for (size_t i = 0; i < StrList->size; ++i) {
        free(StrList->data[i]);
    }
    free(StrList->data);
    free(StrList);
}

size_t StrList_size(const StrList* StrList) {
    return (StrList != NULL) ? StrList->size : 0;
}

void StrList_insertLast(StrList* StrList, const char* data) {
    if (StrList == NULL || data == NULL) return;

     char* newData = (char*)malloc(strlen(data) + 1);

    if (newData == NULL) {
        
        return;
    }

    
    StrList->data = (char**)realloc(StrList->data, (StrList->size + 1) * sizeof(char*));

    
    if (StrList->data == NULL) {
        free(newData);
        return;
    }

    StrList->data[StrList->size] = newData;

    ++StrList->size;
}


void StrList_insertAt(StrList* StrList, const char* data, unsigned int index) {
    if (StrList == NULL || data == NULL || index > StrList->size) return;

    StrList->data = (char**)realloc(StrList->data, (StrList->size + 1) * sizeof(char*));

    for ( unsigned int i = StrList->size; i > index; --i) {
        StrList->data[i] = StrList->data[i - 1];
    }

    
    char* newData = (char*)malloc(strlen(data) + 1);
    strcpy(newData, data);
    StrList->data[index] = newData;

    ++StrList->size;
}

char* StrList_firstData(const StrList* StrList) {
    return (StrList != NULL && StrList->size > 0) ? StrList->data[0] : NULL;
}

void StrList_print(const StrList* StrList) {
    if (StrList == NULL) return;

    for (size_t i = 0; i < StrList->size; ++i) {
        printf("%s ", StrList->data[i]);
    }

    printf("\n");
}

void StrList_printAt(const StrList* StrList,unsigned int index) {
    if (StrList == NULL || index >= StrList->size) return;

    printf("%s\n", StrList->data[index]);
}

int StrList_printLen(const StrList* StrList) {
    if (StrList == NULL) return 0;

    int totalLen = 0;

    for (size_t i = 0; i < StrList->size; ++i) {
        totalLen += strlen(StrList->data[i]);
    
}
    return totalLen;
}

int StrList_count(StrList* StrList, const char* data) {
    if (StrList == NULL || data == NULL) return 0;

    int count = 0;

    for (size_t i = 0; i < StrList->size; ++i) {
        if (strcmp(StrList->data[i], data) == 0) {
            ++count;
        }
    }

    return count;
}

void StrList_remove(StrList* StrList, const char* data) {
    if (StrList == NULL || data == NULL) return;

    size_t newSize = 0;

    for (size_t i = 0; i < StrList->size; ++i) {
        if (strcmp(StrList->data[i], data) != 0) {
            StrList->data[newSize] = StrList->data[i];
            ++newSize;
        } else {
            free(StrList->data[i]);
        }
    }

    StrList->size = newSize;
    StrList->data = (char**)realloc(StrList->data, newSize * sizeof(char*));
}

void StrList_removeAt(StrList* StrList,unsigned int index) {
    if (StrList == NULL || index >= StrList->size) return;

    free(StrList->data[index]);

    for (unsigned int i = index; i < StrList->size - 1; ++i) {
        StrList->data[i] = StrList->data[i + 1];
    }

    --StrList->size;
    StrList->data = (char**)realloc(StrList->data, StrList->size * sizeof(char*));
}

int StrList_isEqual(const StrList* StrList1, const StrList* StrList2) {
    if (StrList1 == NULL || StrList2 == NULL || StrList1->size != StrList2->size) return 0;

    for (size_t i = 0; i < StrList1->size; ++i) {
        if (strcmp(StrList1->data[i], StrList2->data[i]) != 0) {
            return 0;
        }
    }

    return 1;
}
StrList* newStrList ;

StrList* StrList_clone(const StrList* StrList) {
    if (StrList == NULL) return NULL;

    newStrList = StrList_alloc();

    if (newStrList == NULL) {
        // Handle allocation failure
        return NULL;
    }

    for (size_t i = 0; i < StrList->size; ++i) {
        // Use strdup to clone the strings
        char* clonedString = (char*)malloc(strlen(StrList->data[i]) + 1);
        strcpy(clonedString,StrList->data[i]);
    

        // Check for allocation failure (NULL returned by strdup)
        if (clonedString == NULL) {
            // Handle allocation failure (e.g., free allocated memory and return NULL)
            StrList_free(newStrList);
            return NULL;
        }

        StrList_insertLast(newStrList, clonedString);
    }

    return newStrList;
}


void StrList_reverse(StrList* StrList) {
    if (StrList == NULL || StrList->size <= 1) return;

    size_t start = 0;
    size_t end = StrList->size - 1;

    while (start < end) {
        char* temp = StrList->data[start];
        StrList->data[start] = StrList->data[end];
        StrList->data[end] = temp;

        ++start;
        --end;
    }
}

void StrList_sort(StrList* StrList) {
    if (StrList == NULL || StrList->size <= 1) return;

    qsort(StrList->data, StrList->size, sizeof(char*), myCompare);
}

int StrList_isSorted(StrList* StrList) {
    if (StrList == NULL || StrList->size <= 1) return 1;

    for (size_t i = 1; i < StrList->size; ++i) {
        if (strcmp(StrList->data[i - 1], StrList->data[i]) > 0) {
            return 0;
        }
    }

    return 1;
}

