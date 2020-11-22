#include "Akinator.h"


int main (int argc, const char* argv)
{
    setlocale (LC_ALL, "Russian");
    
    //txSpeak ("\vHello! I am Pikachu, i am detective, and i can know what are you thinking about!\n");
    //txSpeak ("\vWhat?! You don't believe me? Ask something\n");
    //txSpeak ("\v Post Scriptum: Tihon Mavrin, idi pomoysa\n");
    
    
    //PrintModes (stdout);
    
    char* command = (char*) calloc (MAX_TEXT_LEN, sizeof (char));
    int mode = 0;
    
    HDC* Pikachu = PikachuIsGettingReady (Pikachu);
    
    Tree* tree = ReadTree ();
    
    while (mode != EXIT)
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
    
    *vertex = {NULL, NULL, NULL};
    
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
            Pikachu [i - '1'] = txLoadImage (name_hello);
        }
        if (i <= '2')
        {
            name_ask [strlen (name_ask) - 5] = i;
            Pikachu [i - '1' + 1] = txLoadImage (name_ask);
        }
        if (i <= '3')
        {
            name_right [strlen (name_right) - 5] = i;
            Pikachu [i - '1' + 3] = txLoadImage (name_right);
        }
        if (i <= '4')
        {
            name_sad [strlen (name_sad) - 5] = i;
            Pikachu [i - '1' + 6] = txLoadImage (name_sad);
            
            name_wrong [strlen (name_wrong) - 5] = i;
            Pikachu[i - '1' + 10] = txLoadImage (name_wrong);
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
        
        case DEFINITION:    //Definition (tree);
                            break;
                            
        case COMPARISION:   //Definition (tree);
                            break;
                            
        case TREE:          LogsMaker (tree->root, "No NULLs");
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

void PlayGame (Node* root, HDC Pikachu[])
{
    if (!txWindow())
    {
        txCreateWindow (512, 512);
        txBitBlt (txDC(), 0, 0, 512, 512, Pikachu[0]);
    }
    
    txSpeak ("\vCannot you, please, think about something?\n");
    txSpeak ("\vTell me, when you'll be ready\n");
    
    char* temp = (char*) calloc (MAX_TEXT_LEN, sizeof (char));          // Подумай как улучшить 
    gets (temp);
    free (temp);
    
    txBitBlt (txDC(), 0, 0, 512, 512, Pikachu[1 + random(2)]);
    
    Checker (root, Pikachu);
}


void Checker (Node* root, HDC Pikachu[])
{
    if (!root->no && !root->yes)
    {
        txSpeak ("\vYou were thinking about %s? ", root->text);
        
        char* temp = (char*) calloc (MAX_TEXT_LEN, sizeof (char));
        gets (temp);
        
        if (strcmpi(temp, "Yes") == 0)
        {
            txBitBlt (txDC(), 0, 0, 512, 512, Pikachu[3 + random(3)]);
            
            txSpeak ("Ooh, that's great, I didn't suspect, that I will win...\n");
            txSpeak ("Maybe we'll do it again?\n");
        }
        else if (strcmpi(temp, "No") == 0)
        {
            txBitBlt (txDC(), 0, 0, 512, 512, Pikachu[10 + random(4)]);
            
            root = InsertNode (root);
            
            txSpeak ("Uh... Sad.\n");
            txSpeak ("Maybe next time will be better?");
        }
        else
            ErrorReport (WRONG_ANSWER, "Checker");
        
        free (temp);
    }
    else
    {
        txSpeak ("\vIs it %s? ", root->text);
        
        char* temp = (char*) calloc (MAX_TEXT_LEN, sizeof (char));
        gets (temp);
        
        if (strcmpi(temp, "Yes") == 0)
        {
            Checker (root->yes, Pikachu);
        }
        else if (strcmpi(temp, "No") == 0)
        {
            Checker (root->no, Pikachu);
        }
        else
            ErrorReport (WRONG_ANSWER, "Checker");
        
        free (temp);
    }
}


Node* InsertNode (Node* vertex)
{
    vertex->yes = NodeConstruct (vertex->yes);
    vertex->no  = NodeConstruct (vertex->no);
    
    vertex->yes->text = vertex->text;
    
    printf ("\nSo what were you thinking about?\n");
    printf ("About ");
    
    char* new_answer = (char*) calloc (MAX_TEXT_LEN, sizeof (char));
    gets (new_answer);
    vertex->no->text = new_answer;
    //free (new_answer);   Делается в destruct
    
    printf ("\nWhat is differense between \"%s\" and \"%s\"? \n", vertex->no->text, vertex->yes->text);
    printf ("%s is not ", vertex->no->text);
    
    char* difference = (char*) calloc (MAX_TEXT_LEN, sizeof (char));
    gets (difference);
    vertex->text = difference;
    //free (difference);   Делается в destruct
    
    return vertex;
}


void SayGoodbye (HDC* Pikachu)
{
    if (!txWindow())
        txCreateWindow (512, 512);
    txBitBlt (txDC(), 0, 0, 512, 512, Pikachu[6 + random(2)]);
    txSpeak ("Bye-bye\n");
}


void Delete_images (HDC Pikachu_ask[])
{
    for (int i = 0; i < 15; i++)
        if (Pikachu_ask[i])
            txDeleteDC (Pikachu_ask[i]);
}
