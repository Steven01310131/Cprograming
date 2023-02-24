#include <stdio.h>
#include <stdlib.h>

// defining the node structure
typedef struct node
{
    int index;         // index value the day of january(1-31)
    float min_temp;    // minimum temperature for the day
    float max_temp;    // maximum temperature for the day
    struct node *next; // pointer to the next node
} node_t;

// head pointer to the linked list
node_t *head = NULL;

// function to print the linked list
void print_list()
{
    // current pointer to the head of the linked list
    node_t *current = head;

    printf("Day     min     max\n");
    // traversing the linked list and printing the values
    while (current != NULL)
    {
        printf("%d      %f     %f\n", current->index, current->min_temp, current->max_temp);
        current = current->next;
    }
    printf("\n");
}

// function to insert a node into the linked list in a sorted manner with no duplicates
void insert(int index, float min_temp, float max_temp)
{
    // current pointer to the head of the linked list
    node_t *current = head;
    // previous pointer to the previous node
    node_t *previous = NULL;

    // creating a new node
    node_t *new_node = (node_t *)malloc(sizeof(node_t));
    new_node->index = index;
    new_node->min_temp = min_temp;
    new_node->max_temp = max_temp;
    new_node->next = NULL;

    // checking if the linked list is empty
    if (head == NULL)
    {
        // assigning the new node to the head of the linked list
        head = new_node;
        return;
    }

    // traversing the linked list to find the location to insert the new node
    while (current != NULL && current->index < index)
    {
        // assigning the current node to the previous node
        previous = current;
        // assigning the next node to the current node
        current = current->next;
    }

    // checking if the new node has the same index as the current node
    if (current != NULL && current->index == index)
    {
        // updating the current node with the new min and max temperatures
        current->min_temp = min_temp;
        current->max_temp = max_temp;
        // freeing the memory allocated to the new node
        free(new_node);
        return;
    }

    // checking if the new node is to be inserted at the head of the linked list
    if (previous == NULL)
    {
        // assigning the new node to the head of the linked list
        head = new_node;
        // assigning the next node to the next of the new node
        new_node->next = current;
    }
    else
    {
        // assigning the new node to the next of the previous node
        previous->next = new_node;
        // assigning the next node to the next of the new node
        new_node->next = current;
    }
}

// function to delete a node from the linked list
void delete(int index)
{
    // current pointer to the head of the linked list
    node_t *current = head;
    // previous pointer to the previous node
    node_t *previous = NULL;

    // checking if the linked list is empty
    if (head == NULL)
    {
        return;
    }

    // traversing the linked list to find the node to be deleted
    while (current != NULL && current->index < index)
    {
        // assigning the current node to the previous node
        previous = current;
        // assigning the next node to the current node
        current = current->next;
    }

    // checking if the node to be deleted is not found
    if (current == NULL)
    {
        return;
    }

    // checking if the node to be deleted is at the head of the linked list
    if (previous == NULL)
    {
        // assigning the next node to the head of the linked list
        head = current->next;
    }
    if(current->index==index)
    {
        // assigning the next node to the next of the previous node
        previous->next = current->next;
        return;
    }

    // freeing the memory allocated to the node to be deleted
    // free(current);
}

int main()
{
    char command;
    int index;
    float min_temp;
    float max_temp;

    // infinite loop to take the user input
    while (1)
    {
        // taking the user input
        printf("Enter command: ");
        scanf(" %c", &command);

        // checking the user input
        switch (command)
        {

        case 'A':
            scanf(" %d %f %f", &index, &min_temp, &max_temp);
            // checking for the index to match the days of january
            if (index < 1 || index > 31)
            {
                printf("Invalid index value. Please enter a value between 1 and 31.\n");
                break;
            }
            insert(index, min_temp, max_temp);
            break;

        case 'D':
            scanf("%d", &index);
            // checking for the index to match the days of january
            if (index < 1 || index > 31)
            {
                printf("Invalid index value. Please enter a value between 1 and 31.\n");
                break;
            }
            delete (index);
            break;

        case 'P':
            print_list();
            break;

        case 'Q':
            return 0;

        default:
            printf("Invalid command. Please enter a valid command.\n");
            break;
        }
    }
}
