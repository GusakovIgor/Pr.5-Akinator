#include "Akinator.h"

FILE* StdLogs = stdout;

void ErrorReport (error_t err_code, const char* func)
{
    if (StdLogs != stderr && StdLogs != stdout)
        printf ("You can see, what is wrong in \"TextLogs.txt\"\n");
    
    fprintf (StdLogs, "\nError with code %d in function \"%s\"\n", err_code, func);
    
    switch (err_code)
    {
        case ALLOCATION_ERROR:  fprintf (StdLogs, "Allocation error: Please, check if you are destructing hole tree and all allocations\n");
                                break;
        
        case WRONG_NODE_PTR:    fprintf (StdLogs, "Wrong Node pointer: Pointer on some node is NULL, please check your code for segfaults\n");
                                break;
        
        case INCORRECT_MODE:    fprintf (StdLogs, "Wrong mode: You didn't enter mode, or mode is incorrect\n");
                                PrintModes (StdLogs);
                                break;
        
        case TREE_FILE_ERROR:   fprintf (StdLogs, "Wrong filling tree file: Number of \"{\" don't match number of \"}\" \n");
                                break;
                                
        case WRONG_FILE_FORMAT: fprintf (StdLogs, "Incorrect file construction, please check that all \"{\" and \"}\" placed correctly\n");
                                fprintf (StdLogs, "and there is no symbols, except \", {, }, and Russian letters\n");
                                break;
        
        case WRONG_ANSWER:      fprintf (StdLogs, "Incorrect input format (Pikachu looks like an adult, but it's not true. He can't understand everything)\n");
                                fprintf (StdLogs, "Please answer \"Yes\" or \"No\"\n");
                                break;
        
        case WRONG_ELEM_NAME:   fprintf (StdLogs, "Wrong name of element in Pikachu's tree (there is no such element, or you've made a mistake)\n");
                                fprintf (StdLogs, "Please check your input\n");
                                break;
    }
    
    assert (!"OK");
}


void PrintModes (FILE* Logs)
{
    
    fprintf (Logs, "\n");
    txSpeak ("\vHere you can see, what modes you can play:\n");
    fprintf (Logs, "1) Game:\n");
    fprintf (Logs, "    -You'll need to make a wish for something and then\n");
    fprintf (Logs, "     Akinator will ask you some questions, trying to find out your wish\n");
    fprintf (Logs, "    -If Akinator is wrong he will ask you what did you wish\n");
    fprintf (Logs, "     and what is the difference between your wish, and something, he guessed\n");
    
    fprintf (Logs, "Don't forget! You should enter \"Game\"!\n\n");
    
    
    fprintf (Logs, "2) Definition:\n");
    fprintf (Logs, "    -You'll give to Akinator subject, that you'll be interested in\n");
    fprintf (Logs, "     and he will tell you all characteristics of this subject, that he knows\n");
    fprintf (Logs, "    -If Akinator don't know anything about subject you are searching for\n");
    fprintf (Logs, "     he will tell you about it, and will invite you in the game mode\n");
    
    fprintf (Logs, "Don't forget! You should enter \"Definition\"!\n\n");
    
    
    fprintf (Logs, "3) Comparision:\n");
    fprintf (Logs, "    -You'll give to Akinator two subjects, which difference you'll need to know\n");
    fprintf (Logs, "     and he will tell you all information about characteristics, that are the same for both subjects\n");
    fprintf (Logs, "     and for once that are different\n");
    fprintf (Logs, "    -If Akinator don't know anything about any subject you are searching for\n");
    fprintf (Logs, "     he will tell you about it, and will invite you in the game mode\n");
    
    fprintf (Logs, "Don't forget! You should enter \"Comparision\"!\n\n");
    
    
    fprintf (Logs, "4) Tree:\n");
    fprintf (Logs, "    -Akinator will show you his secrets!\n");
    fprintf (Logs, "     All his tree of answers will be available for your eyes, mortal!\n");
    
    fprintf (Logs, "Don't forget! You should enter \"Tree\"!\n\n");
    
    
    fprintf (Logs, "5) Exit:\n");
    fprintf (Logs, "    -Akinator will stop waiting for commands from you,\n");
    fprintf (Logs, "     will thank you for game and will say bye\n");
    
    fprintf (Logs, "Don't forget! You should enter \"Exit\"!\n\n");
    
    
    //txSpeak ("\vIf you want to see more, you can call Akinator_help, using this command:\n");
    //fprintf (Logs, "make -f Makefile.txt help\n\n");
}



void LogsMaker (Node* root, char* mode)
{
    int num_mode = (strcmp(mode, "NULL") == 0) ? 1 : 0;
    
    FILE* GraphicLogs = fopen ("Logs\\GraphicLogs.txt", "w");
    static int call = 0;
    
    fprintf (GraphicLogs, "digraph %d {\n", call);
    fprintf (GraphicLogs, "node [shape = \"record\", style = \"filled\", color = \"#000800\", fillcolor = \" #ED96EC\"]\n");
    
    if (root)
    {
        fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", label = \"{%s}\"]\n", 
                                                                            root, root->text);
        if (root->no)
        {
            PrintSubTree (root->no, GraphicLogs, num_mode);
            fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", root, root->no);
        }
        if (root->yes)
        {
            PrintSubTree (root->yes, GraphicLogs, num_mode);
            fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", root, root->yes);
        }
    }
    else if (num_mode)
    {
        fprintf (GraphicLogs, "\"%d\" [color = \"#000800\", fillcolor = blue, label = \"{NULL}\"]\n", 0);
    }
    
    fprintf (GraphicLogs, "}\n");
    
    fclose (GraphicLogs);
    
    
    char* command_1 = (char*) calloc (100, sizeof(char));
    sprintf (command_1, "dot -Tjpeg Logs\\GraphicLogs.txt > Logs\\GraphicLogs_%d.jpeg", call);
    char* command_2 = (char*) calloc (100, sizeof(char));
    sprintf (command_2, "start Logs\\GraphicLogs_%d.jpeg", call);
    
    system (command_1);
    system (command_2);
    
    free (command_1);
    free (command_2);
    
    call++;
}

void PrintSubTree (Node* root, FILE* GraphicLogs, int mode)
{   
    static int check = -1;
    if (root->no || root->yes)
        fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", label = \"{%s}\"]\n", 
                                                                                root, root->text);
    else
        fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", fillcolor = turquoise, label = \"{%s}\"]\n", 
                                                                                root, root->text);
    
    fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n [color = white]", root, root->back);
    
    if (root->no)
    {
        PrintSubTree (root->no, GraphicLogs, mode);
        fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", root, root->no);
    }
    else if (mode)
    {
        fprintf (GraphicLogs, "\"%d\" [color = \"#000800\", fillcolor = blue, label = \"{NULL}\"]\n", check);
        fprintf (GraphicLogs, "\"%p\" -> \"%d\"\n", root, check);
        check--;
    }
    
    if (root->yes)
    {
        PrintSubTree (root->yes, GraphicLogs, mode);
        fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", root, root->yes);
    }
    else if (mode)
    {
        fprintf (GraphicLogs, "\"%d\" [color = \"#000800\", fillcolor = blue, label = \"{NULL}\"]\n", check);
        fprintf (GraphicLogs, "\"%p\" -> \"%d\"\n", root, check);
        check--;
    }
}




void PhysicalLogsMaker (List* lst)
{   
    FILE* GraphicLogs = fopen ("Logs\\GraphicLogs_P.txt", "w");
    
    static int call = 0;
    
    fprintf (GraphicLogs, "digraph %d {\n", call);
    
    MakePlaces (lst, GraphicLogs);
    
    fprintf (GraphicLogs, "node [shape = \"record\", style = \"filled\", color = \"#000800\", fillcolor = \" #C0FFEE\"]\n");
    fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", fillcolor = \"#c81446\", label = \"{NULL | {%d|%d|%d}}\"]\n", &lst->nodes[0], lst->nodes[0].prev, 0, lst->nodes[0].next);
    
    if (lst->size > 0)
    {
        PrintBranch (lst, GraphicLogs, lst->head);
        fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", &lst->nodes[0], &lst->nodes[lst->head]);
    }
    if (lst->size < lst->capacity - 1)
    {
        PrintBranch (lst, GraphicLogs, lst->free);
        fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", &lst->nodes[0], &lst->nodes[lst->free]);
    }

    fprintf (GraphicLogs, "}");
    
    fclose (GraphicLogs);
    
    char* command_1 = (char*) calloc (100, sizeof(char));
    char* command_2 = (char*) calloc (100, sizeof(char));
    sprintf (command_1, "dot -Tjpeg Logs\\GraphicLogs_P.txt > Logs\\GraphicLogs_P%d.jpeg", call);
    sprintf (command_2, "start Logs\\GraphicLogs_P%d.jpeg", call);
    
    system (command_1);
    system (command_2);
    
    free (command_1);
    free (command_2);
    
    call++;
}


void PrintBranch (List* lst, FILE* GraphicLogs, int start_index)
{
    int index = start_index;
    while (index != 0)
    {   
        if (start_index == lst->free)
            fprintf (GraphicLogs, "{rank = same; \"%d\"; \"%p\" [fillcolor = \"#C0FFEE\", label = \"{free | {%d|%d|%d}}\"]; }\n", index,
                                                                            &lst->nodes[index], lst->nodes[index].prev, index, lst->nodes[index].next);
        else if (start_index == lst->head)
            fprintf (GraphicLogs, "{rank = same; \"%d\"; \"%p\" [fillcolor = \"#ED96EC\", label = \"{% | {%d|%d|%d}}\"]; }\n", index,
                                                                        &lst->nodes[index], lst->nodes[index].data, lst->nodes[index].prev, index, lst->nodes[index].next);
        else
        {
            printf ("ERROR in printing list, wrong start_index for branch (free or filled) printing");
            assert (!"OK");
        }
        
        fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", &lst->nodes[index], &lst->nodes[lst->nodes[index].next]);
        if (index != lst->free && index != lst->head)
            fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", &lst->nodes[index], &lst->nodes[lst->nodes[index].prev]);
        
        index = lst->nodes[index].next;
    }
}


void MakePlaces (List* lst, FILE* GraphicLogs)
{
    fprintf (GraphicLogs, "{\n");
    fprintf (GraphicLogs, "node [shape = plaintext, color = white, label = \"\"]\n");
    fprintf (GraphicLogs, "edge [color = white]\n");
    for (int i = 1; i < lst->capacity - 1; i++)                 // Capacity is 1 above max index of usable node
    {
        fprintf (GraphicLogs, "\"%d\" -> ", i);
    }
    fprintf (GraphicLogs, "\"%d\";\n", lst->capacity - 1);
    fprintf (GraphicLogs, "}\n");
}
