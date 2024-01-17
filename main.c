#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib/testlib.h"

#define ARRAYLIST_INITIALCAPACITY 8

typedef struct ArrayList
{
    void* elements;
    size_t elementSize;
    unsigned int length;
    unsigned int capacity;
} ArrayList;

ArrayList* ArrayList_Create(size_t elementSize);
void* ArrayList_GetElementAt(ArrayList* list, int index);
void ArrayList_AddElement(ArrayList* list, void* newElement);
void ArrayList_RemoveElement(ArrayList* list);
void ArrayList_DoubleCapacity(ArrayList* list); 
void ArrayList_ReduceCapacity(ArrayList* list);







// MAIN
int main(int argc, char** argv)
{
    ArrayList* intList = ArrayList_Create(sizeof(int));

    int val = 5;
    ArrayList_AddElement(intList, (void*)&val);
    val = 999;
    ArrayList_AddElement(intList, (void*)&val);
    ArrayList_AddElement(intList, (void*)&val);
    ArrayList_AddElement(intList, (void*)&val);
    ArrayList_AddElement(intList, (void*)&val);
    ArrayList_AddElement(intList, (void*)&val);
    val = 888;
    ArrayList_AddElement(intList, (void*)&val);
    ArrayList_AddElement(intList, (void*)&val);
    ArrayList_AddElement(intList, (void*)&val);

    ArrayList_RemoveElement(intList);
    ArrayList_RemoveElement(intList);
    ArrayList_RemoveElement(intList);
    ArrayList_RemoveElement(intList);
    
    printf("%d\n", *(int*)ArrayList_GetElementAt(intList, 5));

    return 0;
}





ArrayList* ArrayList_Create(size_t elementSize)
{
    ArrayList* list = malloc(sizeof(ArrayList));
    list->elementSize = elementSize;
    list->capacity = ARRAYLIST_INITIALCAPACITY;
    list->length = 0;
    list->elements = malloc(ARRAYLIST_INITIALCAPACITY * elementSize);

    return list;
}

void* ArrayList_GetElementAt(ArrayList* list, int index)
{
    return list->elements + index * list->elementSize;
}

void ArrayList_AddElement(ArrayList* list, void* newElement)
{
    if (list == NULL || list->elements == NULL)
        return;
    
    if (list->length >= list->capacity)
        ArrayList_DoubleCapacity(list);

    char* insertPtr = ((char*)(list->elements) + list->elementSize * list->length);
    
    for (int i = 0; i < list->elementSize; ++i)
        insertPtr[i] = ((char*)newElement)[i];
    ++list->length;

    // printf("%d\n", ((int*)list->elements)[list->length-1] );
}


#define ARRAYLIST_CAPACITYREDUCECONDITION (list->length < list->capacity/2 && list->capacity > 8)
void ArrayList_RemoveElement(ArrayList* list)
{
    if (list == NULL || list->elements == NULL)
        return;
    
    if (list->length <= 0)
        return;

    if (ARRAYLIST_CAPACITYREDUCECONDITION)
        ArrayList_ReduceCapacity(list);
    
    --list->length;
}


void ArrayList_DoubleCapacity(ArrayList* list)
{
    printf("increasing list capacity to %d\n", list->capacity*2);
    list->capacity *= 2;
    realloc(list->elements, list->capacity * list->elementSize);
}


void ArrayList_ReduceCapacity(ArrayList* list)
{
    printf("reducing list capacity to %d\n", list->capacity/2);
    list->capacity /= 2;
    realloc(list->elements, list->capacity * list->elementSize);
}











