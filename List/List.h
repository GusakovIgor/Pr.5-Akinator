#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

struct Node
{
    char* text;
    
    Node* back;
    Node* no;
    Node* yes;
};

typedef char* elem_t;
typedef int   error_t;

const size_t MIN_CAPACITY = 20;

enum errors {MEMORY_ERROR = 1, CAPACITY_ERROR = 2, NULL_POINTER_ACCESS = 3};

struct Lst_Node
{
    elem_t data;
    int    next;
    int    prev;
};

struct List
{
    int head;
    int tail;
    
    size_t size;
    size_t capacity;
    int free;

    Lst_Node* nodes;
};

// List functions
List*   ListConstruct   (size_t capacity);
List*   ListDestruct    (List* lst);
error_t ListStartFiller (List* lst);

int    GetIndex     (List* lst, int logical_index);

int    InsertHead   (List* lst, elem_t value);
int    InsertTail   (List* lst, elem_t value);
elem_t ExtractHead  (List* lst);
elem_t ExtractTail  (List* lst);

int    InsertRandomAfter    (List* lst, int index, elem_t value);
int    InsertRandomBefore   (List* lst, int index, elem_t value);
elem_t ExtractRandom        (List* lst, int index);

List* This_Is_Not_Function_That_You_Need_Because_You_Do_Mot_Need_Sort (List* lst);
//-----------------------------------------


// Protection functions
//error_t Verify (List* lst);
//void    LogsCleaner ();
//void    ListDump    (List* lst, char* func, error_t err);
//void    PrintList   (List* lst, int loud,   error_t err_code);

//void    LogicalLogsMaker  (List* lst);
void    PhysicalLogsMaker (List* lst);

void    MakePlaces        (List* lst, FILE* GraphicLogs);
void    PrintBranch       (List* lst, FILE* GraphicLogs, int start_index);
//-----------------------------------------------------


/*Unit Tests functions
void TestInsert ();
void TestHeadTail   ();
*/
//--------------------






