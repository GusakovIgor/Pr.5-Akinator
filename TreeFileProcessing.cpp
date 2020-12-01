#include "Akinator.h"



Tree* ReadTree ()
{
    Tree* tree = Construct ();
    
    const char* name = "Tree.txt";
    
    size_t size = SizeGetter (name);
    char* buff  = (char*) calloc (size, sizeof (char));
    
    size_t num_symbols = TextReader (name, buff, size);
    
    tree->root = ScanPositive (tree->root, buff);

    return tree;
}


Node* ScanPositive (Node* vertex, char* buff)
{
    vertex = NodeConstruct (vertex);
    char* temp = NULL;
    
    if (buff)
        temp = strtok (buff, "\t\n\"");
    else
        temp = strtok (NULL, "\t\n\"");    // Считываем слово
    
    if (isalpha (temp[0]))
    {
        vertex->text = temp;
        
        temp = strtok (NULL, "\t\n\"");    // Считываем скобочку после слова
        
        if (temp[0] != '}')                 // Если она открывающаяся, то всё по новой
        {
            vertex->yes = ScanPositive (vertex->yes, NULL);     // Вот здесь мы возвращаемся из рекурсии (заканчиваем считывать поддерево)
            vertex->yes->back = vertex;
            
            temp = strtok (NULL, "\t\n\"");                    // Считываем скобочку сразу после конца поддерева, чтобы понять, что дальше
            
            if (temp && temp[0] == '{')                         // Если она открывается, то нам нужно заполнить отрицательное поддерево
            {
                vertex->no = ScanPositive (vertex->no, NULL);
                vertex->no->back = vertex;
            }
                                                                // А иначе нам ничего не нужно, просто cчитываем скобочку сразу после конца поддерева
                                                                // и возвращаемся выше

            temp = strtok (NULL, "\t\n\"");                    // Она 100% закрывающаяся, т.к. все открывающиеся мы пролистали Scan'ом

            if (temp && temp[0] != '}')
                ErrorReport (WRONG_FILE_FORMAT, "ScanPositive");
        }
    }
    else
    {
        printf ("\nTroubles with \"%s\"\n", temp);
        ErrorReport (WRONG_FILE_FORMAT, "ScanPositiveSubTree");
    }
    
    return vertex;
}


void WriteTree (Node* tree, FILE* database)
{
    fprintf (database, "\"%s\"\n", tree->text);
    
    if (tree->yes)
    {
        fprintf (database, "{\n");
        WriteTree (tree->yes, database);
        fprintf (database, "}\n");
    }
    
    if (tree->no)
    {
        fprintf (database, "{\n");
        WriteTree (tree->no, database);
        fprintf (database, "}\n");
    }
}


size_t TextReader (const char* name, char* text, size_t size)
{
    FILE* Tree = fopen(name, "r");
    
    size_t num_symb = fread (text, sizeof(char), size, Tree);
    *(text + num_symb) = '\0';
    
    fclose(Tree);
    
    return num_symb;
}


size_t SizeGetter (const char* name)
{
    FILE* Tree = fopen (name, "r");
    
    struct stat finfo;
    stat (name, &finfo);
    
    size_t size = finfo.st_size;
        
    fclose(Tree);
    
    return size;
}
