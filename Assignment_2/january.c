#include <stdio.h>
#include <stdlib.h>

/*Defining the structure of the linked list*/
typedef struct node {
    int index; // index value the day of january(1-31)
    float min_temp;
    float max_temp;
    struct node * next;
} node_t;
/*Function that prints the linked list*/
void printList(node_t* head){
    node_t* temp=head;
    temp=temp->next;
    printf("Day     min     max\n");
    /*looping through all the linked nodes and printing their values*/
    while (temp!=NULL){
        printf("%d      %f     %f\n",temp->index,temp->min_temp,temp->max_temp);
        temp=temp->next;
    }
    free(temp);
    printf("\n");

}
/*Function which creates a new node and allocates memory for it */
node_t* newNode(int new_index,float new_min_temp,float new_max_temp)
{
    node_t* new_node=(node_t*)malloc(sizeof(node_t));

    new_node->index = new_index;
    new_node->min_temp=new_min_temp;
    new_node->max_temp=new_max_temp;
    new_node->next = NULL;
    return new_node;
}
/*Function which inserts a node in the linked list*/
void insert(node_t* head,node_t* new){
    node_t * temp=head;
    /*searching the linked list to find the location to insert the node
    in the location which will keep the linked list sorted by index value*/
    while(temp->next!=NULL && temp->next->index<=new->index){
        temp=temp->next;
        }
    /*case where a node has the same index as the inserting node*/
    if (temp->index==new->index){
        temp->min_temp=new->min_temp; // We update the existing
        temp->max_temp=new->max_temp; // node with the new min
        free(new);                     // and max temp and then remove the new node from memory
        return;
    }
    /* case where the node with the specific index does not exist in the linked list  */
    else{new->next=temp->next;
    temp->next=new;
    
    
    return;
    }
    
}
/*function to delete the specified node based on its index value*/
void delete(node_t* head,int index){
    node_t * temp=head,*previous;
    /*searching in the linked list until we find a node with the specified index*/
    while(temp->next!=NULL && temp){
        previous=temp;
        temp=temp->next;
        if (temp->index==index){
            previous->next=temp->next;//updating the linked list 
            free(temp);               //and removing the node from memory
            return ;
            
        }
        
    }


    
        
    }



int main(){
    node_t * head = NULL;                     // initializing the linked list
    head = (node_t *) malloc(sizeof(node_t));//allocating memory for the header of the linked list
    int index;
    double min,max;
    char command;
    if (head == NULL) {
        return 1;
    }

    while (1)
    {
        printf(" Enter command: ");
        scanf(" %c", &command);
        switch (command)
        {
        case 'A':
        {

            scanf(" %d %lf %lf", &index, &min, &max);
            if (index < 1 || index > 31)         // checking for the index to match the days of january
            {
                printf(" Invalid index! \r \n");
                break;
            }
            node_t* new=newNode(index,min,max);
            insert(head,new);
            break;
        }
        case 'D':
        {
            scanf("%d",&index);
            if (index < 1 || index > 31)// checking for the index to match the days of january
            {
                printf(" Invalid index! \r \n");
                break;
            }
            delete(head,index);
            break;
        }
        case 'P':
        {
            printList(head);
            break;
        }
        case 'Q':
        {
            return 0;
        }
        default:
        {
            printf(" Invalid command! \r \n");
            break;
        }
        }
    }

}
