#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int index;
    float min_temp;
    float max_temp;
    struct node * next;
} node_t;

void printList(node_t* head){
    node_t* temp=head;
    temp=temp->next;
    printf("Day     min     max\n");
    while (temp!=NULL){
        printf("%d      %f     %f\n",temp->index,temp->min_temp,temp->max_temp);
        temp=temp->next;
    }
    free(temp);
    printf("\n");

}
node_t* newNode(int new_index,float new_min_temp,float new_max_temp)
{
    node_t* new_node=(node_t*)malloc(sizeof(node_t));

    new_node->index = new_index;
    new_node->min_temp=new_min_temp;
    new_node->max_temp=new_max_temp;
    new_node->next = NULL;
    return new_node;
}
void insert(node_t* head,node_t* new){
    node_t * temp=head;
    while(temp->next!=NULL && temp->next->index<=new->index){
        temp=temp->next;
        }
    if (temp->index==new->index){
        temp->min_temp=new->min_temp;
        temp->max_temp=new->max_temp;
        free(new);
        return;
    }
    else{new->next=temp->next;
    temp->next=new;
    
    return;
    }
    
}
void delete(node_t* head,int index){
    node_t * temp=head,*previous;
    while(temp->next!=NULL && temp){
        previous=temp;
        temp=temp->next;
        if (temp->index==index){
            previous->next=temp->next;
            free(temp);
            return ;
            
        }
        
    }


    
        
    }



int main(){

int index;
float min,max;
node_t * head = NULL;
head = (node_t *) malloc(sizeof(node_t));
if (head == NULL) {
    return 1;
}

char command;
    while(1){
        printf("Enter command: ");
        scanf(" %c",&command);
        if(command=='A'){
            scanf("%d %f %f",&index,&min,&max);
            if(min>max){
                printf("Wrong temparature input\n");
                continue;
            }
            if(head->next==NULL){
                head->next=newNode(index,min,max);
            }
            else{
                node_t* new=newNode(index,min,max);
                insert(head,new);
            }

            
        }
        else if(command=='D'){
            scanf("%d",&index);
            delete(head,index);
        }
        else if (command=='P'){
            printList(head);
            continue;
        }
        else if(command=='Q'){
            break;
        }
    }
    



printf("done\n");



}
