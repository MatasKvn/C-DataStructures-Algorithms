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

// Creation, Deletion, Data access
ArrayList* ArrayList_Create(size_t elementSize);
int Arraylist_Destroy(ArrayList* list);
void* ArrayList_GetElementAt(ArrayList* list, int index);

// Insertion
void ArrayList_AddElement(ArrayList* list, void* newElement);
int ArrayList_InsertElementAt(ArrayList* list, int index, void* newElement);

// Deletion
int ArrayList_RemoveLastElement(ArrayList* list);
int ArrayList_RemoveElementAt(ArrayList* list, int index);

// Capacity change
void ArrayList_DoubleCapacity(ArrayList* list); 
void ArrayList_ReduceCapacity(ArrayList* list);

// Sort
void ArrayList_QSort(ArrayList* list, int (*_PtFuncCompare)(const void *, const void *));

int ArrayList_ContainsElement(ArrayList* list, void* element);
int ArrayList_IndexOf(ArrayList* list, void* element);
int ArrayList_RemoveElement(ArrayList* list, void* element);



// TEST
int _compareIntPtrFunc(const void* a, const void* b)
{
    int** a_ = a;
    int** b_ = b;
    return (**a_)-(**b_);
}

// MAIN
int main(int argc, char** argv)
{
    


//STRINGS
    // ArrayList* strList = ArrayList_Create(sizeof(char[20]));
    // char a[20] = "niggger";
    // char b[20] = "aksjldf";
    // char c[20] = "banana";
    // char d[20] = "helpme";



    // ArrayList_AddElement(strList, (void*)&a);
    // ArrayList_AddElement(strList, (void*)&b);
    // ArrayList_AddElement(strList, (void*)&c);
    // ArrayList_AddElement(strList, (void*)&d);

    

    // for(int i = 0; i < strList->length; ++i)
    //     printf("%d\n", ((char*)ArrayList_GetElementAt(strList, i)) == a );
//INT*
    ArrayList* intPtrList = ArrayList_Create(sizeof(int*));


    int a = 1;
    int b = 99;
    int c = 9;
    int d = 120;
    int e = 0;

    int* a_ = &a;
    int* b_ = &b;
    int* c_ = &c;
    int* d_ = &d;
    int* e_ = &e;
    




    ArrayList_AddElement(intPtrList, (void*)&a_);
    ArrayList_AddElement(intPtrList, (void*)&b_);
    ArrayList_AddElement(intPtrList, (void*)&c_);
    ArrayList_AddElement(intPtrList, (void*)&d_);
    ArrayList_AddElement(intPtrList, (void*)&e_);

    a = 55;
    ArrayList_QSort(intPtrList, _compareIntPtrFunc);

    for(int i = 0; i < intPtrList->length; ++i){
        int** t1 = ArrayList_GetElementAt(intPtrList, i);
        printf("%d ", *t1 == a_);
        printf("%d\n", **t1);
    }
    

    // while (intPtrList->length > 0)
    //     ArrayList_RemoveLastElement(intPtrList);

    // int nig = 999;
    // int* nigPt = &nig;
    // int **nigPtPt = &nigPt;
    // ArrayList_AddElement(intPtrList, (void*)nigPtPt);

    if (ArrayList_ContainsElement(intPtrList, (void*)(&a_)))
    {
        printf("contains\n");
    } else {
        printf("doesn't contain.\n");
    }

    printf("Index of: %d\n", ArrayList_IndexOf(intPtrList, &d_));

    for(int i = 0; i < intPtrList->length; ++i){
        int** t1 = ArrayList_GetElementAt(intPtrList, i);
        printf("%d\n", **t1);
    }

    ArrayList_RemoveElement(intPtrList, &c_);
    printf("\n");
    for(int i = 0; i < intPtrList->length; ++i){
        int** t1 = ArrayList_GetElementAt(intPtrList, i);
        printf("%d\n", **t1);
    }

//INTS
    // ArrayList* intList = ArrayList_Create(sizeof(int));

    // int val = 999;
    // ArrayList_AddElement(intList, (void*)&val);
    // val = 1;
    // ArrayList_AddElement(intList, (void*)&val);

    // // ArrayList_QSort(intList, _compareIntFN);

    // for(int i = 0; i < intList->length; ++i)
    //     printf("%d\n", *(int*)ArrayList_GetElementAt(intList, i));


    
    // val = 1;
    // if (ArrayList_ContainsElement(intList, (void*)&val))
    // {
    //     printf("contains\n");
    // } else {
    //     printf("doesn't contain.");
    // }


    // Arraylist_Destroy(intList);

    return 0;
}

int ArrayList_RemoveElement(ArrayList* list, void* element)
{
    int index = ArrayList_IndexOf(list, element);
    if (index == -1)
        return -0;

    ArrayList_RemoveElementAt(list, index);
    return 1;
}


int ArrayList_IndexOf(ArrayList* list, void* element)
{
    for (int i = 0; i < list->length; ++i)
    {
        if (memcmp((char*)list->elements + i * list->elementSize, (char*)element, list->elementSize) == 0)
            return i;
    }
    return -1;
}

int ArrayList_ContainsElement(ArrayList* list, void* element)
{
    for (int i = 0; i < list->length; ++i)
    {
        if (memcmp((char*)list->elements + i * list->elementSize, (char*)element, list->elementSize) == 0)
            return 1;
    }
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

int Arraylist_Destroy(ArrayList* list)
{
    if (list == NULL)
        return 0;

    free(list->elements);
    free(list);
    return 1;
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

int ArrayList_InsertElementAt(ArrayList* list, int index, void* newElement)
{
    if (list == NULL || list->elements == NULL)
        return 0;
    
    if (index < 0 || index > list->length)
        return 0;

    if (list->length >= list->capacity)
        ArrayList_DoubleCapacity(list);

    for (int i = list->length-1; i >= index; --i)
    {
        memcpy((list->elements + list->elementSize * (i+1)), (list->elements + list->elementSize * i), list->elementSize);
    }
    memcpy((list->elements + list->elementSize * index), newElement, list->elementSize);
    ++list->length;

    return 1;
}


// Deletion
#define ARRAYLIST_CAPACITYREDUCECONDITION (list->length < list->capacity/2 && list->capacity > 8)
int ArrayList_RemoveLastElement(ArrayList* list)
{
    if (list == NULL || list->elements == NULL)
        return 0;
    
    if (list->length <= 0)
        return 0;

    if (ARRAYLIST_CAPACITYREDUCECONDITION)
        ArrayList_ReduceCapacity(list);
    
    --list->length;
    return 0;
}

int ArrayList_RemoveElementAt(ArrayList* list, int index)
{
    if (list == NULL || list->elements == NULL)
        return 0;
    
    if (index < 0 || index >= list->length)
        return 0;

    if (list->length <= 0)
        return 0;

    if (ARRAYLIST_CAPACITYREDUCECONDITION)
        ArrayList_ReduceCapacity(list);

    for (int i = index; i <= list->length; ++i)
    {
        memcpy((list->elements + i * list->elementSize), (list->elements + (i+1) * list->elementSize), list->elementSize);
    }
    --list->length;
    return 1;
}


// Capacity management
void ArrayList_DoubleCapacity(ArrayList* list)
{
    list->capacity *= 2;
    realloc(list->elements, list->capacity * list->elementSize);
}

void ArrayList_ReduceCapacity(ArrayList* list)
{
    list->capacity /= 2;
    realloc(list->elements, list->capacity * list->elementSize);
}

// Sort
void ArrayList_QSort(ArrayList* list, int (*_PtFuncCompare)(const void *, const void *))
{
    qsort(list->elements, list->length, list->elementSize, _PtFuncCompare);
}










