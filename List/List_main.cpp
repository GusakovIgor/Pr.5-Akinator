#include "List.h"

// LIST FUNCTIONS-----------------------------------------------------------------------------
List* ListConstruct (size_t capacity)
{
    
    capacity++;         // Cause we indexing from 0, but use zero element as error indexing (like NULL indexing)
    if (capacity == 0)
    {
        int err = 1;
    }
    if (capacity < MIN_CAPACITY)
    {
        capacity = MIN_CAPACITY + 1;
    }
    
    List* lst = (List*) calloc (1, sizeof (List));
    
    lst->nodes = (Lst_Node*) calloc (capacity, sizeof (Lst_Node));
    assert (lst->nodes);
    
    lst->capacity = capacity;
    
    lst->head = 0;
    lst->tail = 0;
    lst->free = 1;
    
    lst->size = 0;
    
    error_t err = ListStartFiller (lst);
    assert (!err);
    
    return lst;
}


List* ListDestruct (List* lst)
{
    free (lst->nodes);
    free (lst);
    
    return NULL;
}


error_t ListStartFiller (List* lst)
{
    for (int i = 1; i < lst->capacity; i++)
    {
        lst->nodes[i].next = (i < lst->capacity - 1) ? (i + 1) : 0;
        lst->nodes[i].prev = (i > 1                ) ? (i - 1) : 0;
    }
    
    assert (lst->nodes[0].data == 0);
    assert (lst->nodes[0].next == 0);
    assert (lst->nodes[0].prev == 0);
    
    return 0;
}


int InsertHead (List* lst, elem_t value)
{
    int index = InsertRandomAfter (lst, 0, value);
    
    return index;
}


int InsertTail (List* lst, elem_t value)
{
    
    int index = InsertRandomAfter (lst, lst->tail, value);
    
    return index;
}


elem_t ExtractHead (List* lst)
{
    
    elem_t value = ExtractRandom (lst, lst->head);
    
    
    return value;
}


elem_t ExtractTail (List* lst)
{

    elem_t value = ExtractRandom (lst, lst->tail);

}

int InsertRandomBefore (List* lst, int index, elem_t value)
{
    assert (index > 0);
    
    return InsertRandomAfter (lst, lst->nodes[index].prev, value);
}


int InsertRandomAfter (List* lst, int index, elem_t value)
{
    
    int old_free = lst->free;
    lst->free = lst->nodes[old_free].next;
    lst->nodes[lst->free].prev = 0;
    
    lst->nodes[old_free].prev = index;
    lst->nodes[old_free].data = value;
    
    if (index == 0)
    {
        lst->nodes[old_free].next = lst->head;
        lst->head = old_free;
    }
    else
    {
        lst->nodes[old_free].next = lst->nodes[index].next;
    }
    
    if (index != 0)
        lst->nodes [lst->nodes[old_free].prev].next  = old_free;
    
    if (lst->nodes[old_free].next != 0)
        lst->nodes[lst->nodes[old_free].next].prev = old_free; 
    
    if (index == lst->tail)
    {
        lst->tail = old_free;
    }
    
    lst->size++;
    
    return old_free;
}

elem_t ExtractRandom (List* lst, int index)
{
    if (index != lst->head)
        lst->nodes[lst->nodes[index].prev].next = lst->nodes[index].next;
    if (index != lst->tail)
        lst->nodes[lst->nodes[index].next].prev = lst->nodes[index].prev;
    
    elem_t value = lst->nodes[index].data;
    
    if (index == lst->head)
        lst->head = lst->nodes[index].next;
    if (index == lst->tail)
        lst->tail = lst->nodes[index].prev;
        
    lst->nodes[index].next = lst->free;
    lst->nodes[index].prev = 0;
    if (lst->free)
        lst->nodes[lst->free].prev = index;
    
    lst->free = index;
    
    lst->size--;
    
    return value;
}

int GetIndex (List* lst, int logical_index)
{
    int count = 1;
    int iter  = lst->head;
    
    while (iter != 0)
    {
        if (count == logical_index)
            break;
            
        count++;
        iter = lst->nodes[iter].next;
    }
    
    return iter;
}


List* This_Is_Not_Function_That_You_Need_Because_You_Do_Mot_Need_Sort (List* lst)
{
    
}


// END OF LIST FUNCTIONS----------------------------------------------------------------------





