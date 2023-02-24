#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct temperatures
{
    int day; 
    float min, max;
    struct temperatures* next;
} dayTemperatures;

dayTemperatures* monthRoot = NULL;

dayTemperatures* createNode(int index, float min, float max, dayTemperatures* node)
{
    dayTemperatures* newNode = (dayTemperatures*)malloc( sizeof(dayTemperatures) );
    newNode->day = index;
    newNode->max = max; 
    newNode->min = min;
    newNode->next = node;

    return( newNode );
} // createNode

dayTemperatures* updateNode(int index, float min, float max, dayTemperatures* node)
{
    node->max = max; 
    node->min = min;

    return( node );
} // updateNode

void addUpdateNode( int index, float min, float max )
{
    // Start from root.
    dayTemperatures** pnode = &monthRoot;

    // Find a place for our node.
    while (*pnode != NULL && index > (*pnode)->day) 
        pnode = &((*pnode)->next); 

    // Allocate and store data, or update existing node.
    *pnode = (*pnode != NULL && index == (*pnode)->day) ? updateNode( index, min, max, *pnode ) : 
                                                          createNode( index, min, max, *pnode );
} // addUpdateNode

void removeNode( int index )
{
    // We need to keep both the node and its parent.
    dayTemperatures*  node = monthRoot;
    dayTemperatures* pnode = monthRoot;
    while( node != NULL )
    {
        if( node->day == index )
        {
            if( node == monthRoot )
                monthRoot = monthRoot->next;
            else
                pnode->next = node->next;

            free( node );
            return;
        }
        pnode = node;
        node  = node->next;
    }
} // removeNode

void addTemperatures(char* s)
{
    char command = 0;
    int index = 0; 
    float min =0.0, max = 0.0;

    // Parse values. 
    sscanf( s, "%c %d %f %f", &command, &index, &min, &max );
    if( index < 1 || index > 31 )
    {
        printf("Index must be in [1, 31]\n");
        return;
    }

    addUpdateNode( index, min, max );
} // addTemperatures

void deleteTemperatures(char* s)
{
    char command = 0;
    int index = 0; 

    // Parse values. 
    sscanf( s, "%c %d", &command, &index );
    if( index < 1 || index > 31 )
    {
        printf("Index must be in [1, 31]\n");
        return;
    }

    removeNode( index );
} // deleteTemperatures

void printTemperatures()
{
    dayTemperatures* node = monthRoot;
    printf("day\tmin\tmax\n");
    while( node != NULL )
    {
        printf("%*d\t%10.6f\t%10.6f\n", 2, node->day, node->min, node->max );
        node = node->next;
    }
} // printTemperatures

char doMenu(char* s)
{
    // Display menu.
    printf("Enter command: ");

    // Get user choice command.
    fgets( s, 50, stdin );

    return( toupper(s[0]) );
} // doMenu

int main(int argc, char** argv) 
{
    char c = 0;
    char s[255] = "";
    while( (c = doMenu( s )) != 'Q' )
    {
        switch(c)
        {
            case 'A':
                addTemperatures( s );
                break;

            case 'D':
                deleteTemperatures( s );
                break;

            case 'P':
                printTemperatures();
                break;

            default:
                printf("\n*** Wrong choice. Try again. *** \n");
                break;
        }
    }
} // main