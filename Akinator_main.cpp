#include "Akinator.h"


int main (int argc, const char* argv)
{
    setlocale (LC_ALL, "Russian");
    
//    txSpeak ("\vSpokoynoy nochi, Kolya\n");
    txSpeak ("\vHello! I am Pikachu, i am detective, and i can know what are you thinking about!\n");
    txSpeak ("\v\aWhat?! You don't believe me? Ask something\n\n");
//    txSpeak ("\v Post Scriptum: Tihon Mavrin, idi pomoysa\n");
//    txSpeak ("\vBuka\n");
    
    PrintModes (stdout);
    
    char* command = (char*) calloc (MAX_TEXT_LEN, sizeof (char));
    int mode = 0;
    
    HDC* Pikachu = PikachuIsGettingReady (Pikachu);
    
    Tree* tree = ReadTree ();
    
    while (mode != EXIT && mode != BREAK)
    {
        gets (command);
        if (command)
            mode = ModeDetector (command);
        else
            ErrorReport (INCORRECT_MODE, "main");
        
        Akinator (tree, mode, Pikachu);
    }
    
    free (command);
    
    return 0;
}


// Construct-Destruct
Tree* Construct ()
{
    Tree* tree = (Tree*) calloc (1, sizeof (Tree));
    tree->root = NULL;
    
    if (!tree)
        ErrorReport (ALLOCATION_ERROR, "Construct");
    
    return tree;
}

Tree* Destruct  (Tree* tree)
{
    tree->root = NodeDestruct (tree->root);
    
    assert (!tree->root);
    
    return NULL;
}


Node* NodeConstruct (Node* vertex)
{
    vertex = (Node*) calloc (1, sizeof (Node));
    
    if (!vertex)
        ErrorReport (ALLOCATION_ERROR, "NodeConstruct");
    
    *vertex = {NULL, NULL, NULL, NULL};
    
    return vertex;
}

Node* NodeDestruct  (Node* vertex)
{
    if (vertex->no)
        vertex->no  = NodeDestruct (vertex->no);
        
    if (vertex->yes)
        vertex->yes = NodeDestruct (vertex->yes);
        
    free (vertex);
    vertex = NULL;
    
    return vertex;
}
//----------------------



// Functions
HDC* PikachuIsGettingReady (HDC* Pikachu)
{
    Pikachu = (HDC*) calloc (15, sizeof (HDC));
    
    char name_hello [MAX_TEXT_LEN] = "Pikachu Detective\\PikachuDetective_hello .bmp";
    char name_ask   [MAX_TEXT_LEN] = "Pikachu Detective\\PikachuDetective_ask .bmp";
    char name_right [MAX_TEXT_LEN] = "Pikachu Detective\\PikachuDetective_right .bmp";
    char name_sad   [MAX_TEXT_LEN] = "Pikachu Detective\\PikachuDetective_sad .bmp";
    char name_wrong [MAX_TEXT_LEN] = "Pikachu Detective\\PikachuDetective_wrong .bmp";
    
    
    for (char i = '1'; i <= '4'; i++)
    {
        
        if (i == '1')
        {
            name_hello [strlen (name_hello) - 5] = i;
            Pikachu [i - '1' + HELLO] = txLoadImage (name_hello);
        }
        if (i <= '2')
        {
            name_ask [strlen (name_ask) - 5] = i;
            Pikachu [i - '1' + ASK]   = txLoadImage (name_ask);
        }
        if (i <= '3')
        {
            name_right [strlen (name_right) - 5] = i;
            Pikachu [i - '1' + RIGHT] = txLoadImage (name_right);
        }
        if (i <= '4')
        {
            name_sad [strlen (name_sad) - 5] = i;
            Pikachu [i - '1' + SAD]   = txLoadImage (name_sad);
            
            name_wrong [strlen (name_wrong) - 5] = i;
            Pikachu [i - '1' + WRONG] = txLoadImage (name_wrong);
        }
    }
    
    return Pikachu;
}


/*char** PikachuIsLearningToTalk (char** phrases)
{
    phrases = (char**) calloc (15, sizeof (char*));
    for (int i = 0; i < 15; i++)
        phrases[i] = (char*) calloc (2*MAX_TEXT_LEN, sizeof (char));
    
    phrases[0] = "Hello!!! I'm so happy to see you, let's play a game";
}*/


int ModeDetector (const char* mode)
{
    if (strcmp (mode, "Game") == 0)
    {
        return GAME;
    }
    else if (strcmp (mode, "Definition") == 0)
    {
        return DEFINITION;
    }
    else if (strcmp (mode, "Comparision") == 0)
    {
        return COMPARISION;
    }
    else if (strcmp (mode, "Tree") == 0)
    {
        return TREE;
    }
    else if (strcmp (mode, "Exit") == 0)
    {
        return EXIT;
    }
    else if (strcmp (mode, "Break") == 0)
    {
        return BREAK;
    }
    else
    {
        ErrorReport (INCORRECT_MODE, "ModeDetector");
    }
}


void Akinator (Tree* tree, int mode, HDC Pikachu[])
{
    
    switch (mode)
    {
        case GAME:          PlayGame (tree->root, Pikachu);
                            break;
        
        case DEFINITION:    Definition (tree);
                            break;
        
        case COMPARISION:   Comparision (tree);
                            break;
        
        case TREE:          LogsMaker (tree->root, "No NULLs");
                            break;
        
        case BREAK:         txSpeak ("\v\aDurashka ");
                            printf  ("<3\n");
                            Delete_images (Pikachu);
                            tree = Destruct (tree);
                            break;
        
        case EXIT:          SayGoodbye (Pikachu);
                            Delete_images (Pikachu);
                            
                            FILE* database = fopen ("Tree.txt", "w");
                            WriteTree (tree->root, database);
                            fclose (database);
                            
                            tree = Destruct (tree);
                            break;
    }
    
}
//----------------------


// Game
void PlayGame (Node* root, HDC Pikachu[])
{
    if (!txWindow())
        txCreateWindow (512, 512);
    txBitBlt (txDC(), 0, 0, 512, 512, Pikachu[HELLO]);
    
    txSpeak ("\vCannot you, please, think about something?\n");
    txSpeak ("\v\aTell me, when you'll be ready\n");
    
    char* temp = (char*) calloc (MAX_TEXT_LEN, sizeof (char));
    gets (temp);
    free (temp);
    
    txBitBlt (txDC(), 0, 0, 512, 512, Pikachu[ASK + Random(2)]);
    
    Checker (root, Pikachu);
}


void Checker (Node* root, HDC Pikachu[])
{
    Node* pointer = root;
    char* temp = (char*) calloc (MAX_TEXT_LEN, sizeof (char));
    
    while (pointer->no || pointer->yes)
    {
        txSpeak ("\v\aIs it %s? ", pointer->text);
        gets (temp);
        
        if (strcmpi (temp, "Yes") == 0)
        {
            pointer = pointer->yes;
        }
        else if (strcmpi (temp, "No") == 0)
        {
            pointer = pointer->no;
        }
        else
            ErrorReport (WRONG_ANSWER, "Checker");
    }
    
    txSpeak ("\v\aYou were thinking about %s? ", pointer->text);
    gets (temp);
        
    if (strcmpi(temp, "Yes") == 0)
    {
        txBitBlt (txDC(), 0, 0, 512, 512, Pikachu[RIGHT + Random (3)]);
            
        txSpeak ("\vOoh, that's great, I didn't suspect, that I will win...\n");
        txSpeak ("\v\aMaybe we'll do it again?\n");
        
        gets (temp);
        if (strcmpi (temp, "Yes") == 0)
            PlayGame (root, Pikachu);
    }
    else if (strcmpi(temp, "No") == 0)
    {
        txBitBlt (txDC(), 0, 0, 512, 512, Pikachu[WRONG + Random(4)]);
            
        pointer = InsertNode (pointer);
            
        txSpeak ("\vUh... Sad.\n");
        txSpeak ("\v\aMaybe next time will be better?\n");
        
        gets (temp);
        if (strcmpi (temp, "Yes") == 0)
            PlayGame (root, Pikachu);
    }
    else
        ErrorReport (WRONG_ANSWER, "Checker");
        
    free (temp);
    
}


Node* InsertNode (Node* vertex)
{
    vertex->yes = NodeConstruct (vertex->yes);
    vertex->no  = NodeConstruct (vertex->no);
    vertex->yes->back = vertex;
    vertex->no->back  = vertex;
    
    vertex->yes->text = vertex->text;
    
    txSpeak ("\v\a\nSo what were you thinking about?\n");
    printf ("About ");
    
    char* new_answer = (char*) calloc (MAX_TEXT_LEN, sizeof (char));
    gets (new_answer);
    vertex->no->text = new_answer;
    //free (new_answer);   Делается в destruct
    
    txSpeak ("\v\a\nWhat is differense between \"%s\" and \"%s\"? \n", vertex->no->text, vertex->yes->text);
    printf ("%s is not ", vertex->no->text);
    
    char* difference = (char*) calloc (MAX_TEXT_LEN, sizeof (char));
    gets (difference);
    vertex->text = difference;
    //free (difference);   Делается в destruct
    
    return vertex;
}
//----------------------


// Definition - Comparision
void Definition (Tree* tree)
{
    txSpeak ("\vPlease, enter the object's name\n");
    char* name = (char*) calloc (MAX_TEXT_LEN, sizeof (char));
    gets (name);
    
    Node* object = Find (tree->root, name);
    if (!object)
        ErrorReport (WRONG_ELEM_NAME, "Definition");
    
    free (name);
    
    List* lst = ListConstruct (MAX_HEIGHT);
    
    int index = 0;
    index = InsertHead (lst, object->text);
    index = Filler     (lst, object, tree->root, index);
    
    char* temp = NULL;
    while (lst->size > 1)
    {
        index = lst->nodes[lst->tail].prev;
        
        temp  = ExtractRandom (lst, lst->nodes[index].next);
        
        printf ("%s\n", temp);
        
        free (temp);
    }
    
    lst = ListDestruct (lst);
}

Node* Find (Node* root, char* name)
{
    if (strcmpi (root->text, name))   
    {
        Node* temp = NULL;
        if (root->yes)
        {
            temp = Find (root->yes, name);
            if (temp)
                return temp;
        }
    
        if (root->no)
        {
            temp = Find (root->no, name);
            if (temp)
                return temp;
        }
        return NULL;
    }
    else if (!root->no && !root->yes)
    {
        return root;
    }
    else
    {
        return NULL;
    }
}

int Filler (List* lst, Node* object, Node* root, int index)
{  
    char* temp = NULL;
    
    while (object != root)
    {
        temp = (char*) calloc (MAX_TEXT_LEN + 6, sizeof (char));
        
        if (object != root && object->back->no == object)
            strcpy (temp, "- Not \0");
        else
            strcpy (temp, "- ");
        
        object = object->back;
        
        strcat_s (temp, MAX_TEXT_LEN + 6, object->text);
        
        index  = InsertRandomAfter (lst, index, temp);
    }
    
    return index;
}


void Comparision (Tree* tree)
{
   txSpeak ("\v\aPlease, enter first object's name\n");
    char* name = (char*) calloc (MAX_TEXT_LEN, sizeof (char));
    gets (name);
    Node* object = Find (tree->root, name);
    
    List* lst_1 = ListConstruct (MAX_HEIGHT);
    int index = 0;
    index = InsertHead (lst_1, object->text);
    index = Filler (lst_1, object, tree->root, index);
    
    txSpeak ("\v\aAnd second\n");
    gets (name);
    object = Find (tree->root, name);
    
    List* lst_2 = ListConstruct (MAX_HEIGHT);
    index = 0;
    index = InsertHead (lst_2, object->text);
    index = Filler (lst_2, object, tree->root, index);
    
    free (name);
    
    PrintProperties (lst_1, lst_2);
    
    lst_1 = ListDestruct (lst_1);
    lst_2 = ListDestruct (lst_2);
}

void PrintProperties (List* lst_1, List* lst_2)
{
    char* temp_1 = ExtractTail (lst_1);
    char* temp_2 = ExtractTail (lst_2);
    
    bool same = (strcmp (temp_1, temp_2) == 0) ? true : false;
    if (same)
        printf ("Both are:\n");
    else
        printf ("Suddenly, they have nothing in common\n");
        
    while (same && lst_1->size > 1 && lst_2->size > 1)
    {   
        printf ("%s\n", temp_1);
        
        free (temp_1);
        free (temp_2);
        temp_1 = ExtractTail (lst_1);
        temp_2 = ExtractTail (lst_2);
        
        same   = (strcmp (temp_1, temp_2) == 0) ? true : false;
    }
    
    if (lst_1->size > 0)
    {
        printf ("\nBut %s is:\n", ExtractHead (lst_1));
        PrintDifference (lst_1, temp_1);
    }
    
    if (lst_2->size > 0)
    {
        printf ("\nAnd %s is:\n", ExtractHead (lst_2));
        PrintDifference (lst_2, temp_2);
    }
    
}

void PrintDifference (List* lst, char* temp)
{
    printf ("%s\n", temp);
    free   (temp);
        
    while (lst->size > 0)
    {
        temp = ExtractTail (lst);
        printf ("%s\n", temp);
        
        free (temp);
    }
}
//----------------------


// Exit
void SayGoodbye (HDC* Pikachu)
{
    if (!txWindow())
        txCreateWindow (512, 512);
    txBitBlt (txDC(), 0, 0, 512, 512, Pikachu[SAD + Random(2)]);
    txSpeak ("\v\aBye-bye\n");
}


void Delete_images (HDC Pikachu_ask[])
{
    for (int i = 0; i < 15; i++)
        if (Pikachu_ask[i])
            txDeleteDC (Pikachu_ask[i]);
}


int Random (int border)
{
    srand(time(NULL));
    
    return rand () % border;
}
//----------------------
