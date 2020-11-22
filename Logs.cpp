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
    }
    
    assert (!"OK");
}


void PrintModes (FILE* Logs)
{
    
    fprintf (Logs, "\n");
    //txSpeak ("\vHere you can see, what modes you can play:\n");
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
    fprintf (Logs, "make -f Makefile.txt help\n\n");
}


void TreeDump (Tree* tree)
{
    
}



void LogsMaker (Node* root, char* mode)
{
    int num_mode = (strcmp(mode, "NULL") == 0) ? 1 : 0;
    
    FILE* GraphicLogs = fopen ("GraphicLogs.txt", "w");
    static int call = 0;
    
    fprintf (GraphicLogs, "digraph %d {\n", call);
    fprintf (GraphicLogs, "node [shape = \"record\", style = \"filled\", color = \"#000800\", fillcolor = \" #ED96EC\"]\n");
    
    if (root)
    {
        fprintf (GraphicLogs, "\"%p\" [color = \"#000800\", label = \"{%s}\"]\n", 
                                                                            root, root->text);
        if (root->no != NULL)
        {
            PrintSubTree (root->no, GraphicLogs, num_mode);
            fprintf (GraphicLogs, "\"%p\" -> \"%p\"\n", root, root->no);
        }
        if (root->yes != NULL)
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
    sprintf (command_1, "dot -Tjpeg GraphicLogs.txt > GraphicLogs_%d.jpeg", call);
    char* command_2 = (char*) calloc (100, sizeof(char));
    sprintf (command_2, "start GraphicLogs_%d.jpeg", call);
    
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


