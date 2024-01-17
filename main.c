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
void Arraylist_Destroy(ArrayList* list);
void* ArrayList_GetElementAt(ArrayList* list, int index);

void ArrayList_AddElement(ArrayList* list, void* newElement);
void ArrayList_InsertElementAt(ArrayList* list, int index, void* newElement);

void ArrayList_RemoveElement(ArrayList* list);
void ArrayList_RemoveElementAt(ArrayList* list, int index);

void ArrayList_DoubleCapacity(ArrayList* list); 
void ArrayList_ReduceCapacity(ArrayList* list);











// MAIN
int main(int argc, char** argv)
{
    ArrayList* intList = ArrayList_Create(sizeof(int));

    int val = 999;
    ArrayList_AddElement(intList, (void*)&val);
    val = 1;
    ArrayList_AddElement(intList, (void*)&val);
    val = 2;
    ArrayList_AddElement(intList, (void*)&val);
    val = 3;
    ArrayList_AddElement(intList, (void*)&val);
    val = 5;

    // for (int i = 0; i < 34; ++i)
    // {
    //     val = i;
    //     ArrayList_AddElement(intList, (void*)&val);
    // }

    val = 88;
    ArrayList_InsertElementAt(intList, 0, (void*)&val);
    ArrayList_RemoveElementAt(intList, 0);
    ArrayList_RemoveElementAt(intList, 3);

    for(int i = 0; i < intList->length; ++i)
        printf("%d\n", *(int*)ArrayList_GetElementAt(intList, i));

    Arraylist_Destroy(intList);

    return 0;
}




// Creation
ArrayList* ArrayList_Create(size_t elementSize)
{
    ArrayList* list = malloc(sizeof(ArrayList));
    list->elementSize = elementSize;
    list->capacity = ARRAYLIST_INITIALCAPACITY;
    list->length = 0;
    list->elements = malloc(ARRAYLIST_INITIALCAPACITY * elementSize);

    return list;
}

void Arraylist_Destroy(ArrayList* list)
{
    free(list->elements);
    free(list);
}

// Access
void* ArrayList_GetElementAt(ArrayList* list, int index)
{
    return list->elements + index * list->elementSize;
}


// Insertion
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
}

void ArrayList_InsertElementAt(ArrayList* list, int index, void* newElement)
{
    if (list == NULL || list->elements == NULL)
        return;
    
    if (index < 0 || index > list->length)
        return;

    if (list->length >= list->capacity)
        ArrayList_DoubleCapacity(list);

    for (int i = list->length-1; i >= index; --i)
    {
        memcpy((list->elements + list->elementSize * (i+1)), (list->elements + list->elementSize * i), list->elementSize);
    }
    memcpy((list->elements + list->elementSize * index), newElement, list->elementSize);
    ++list->length;
}


// Deletion
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

void ArrayList_RemoveElementAt(ArrayList* list, int index)
{
    if (list == NULL || list->elements == NULL)
        return;
    
    if (index < 0 || index >= list->length)
        return;

    if (list->length <= 0)
        return;

    if (ARRAYLIST_CAPACITYREDUCECONDITION)
        ArrayList_ReduceCapacity(list);

    for (int i = index; i <= list->length; ++i)
    {
        memcpy((list->elements + i * list->elementSize), (list->elements + (i+1) * list->elementSize), list->elementSize);
    }
    --list->length;
}


// Capacity management
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











