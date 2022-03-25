#include<stdlib.h>
#include<stdio.h>

struct list {
	int data;
	struct list* next;
};

struct list* head;

int count_elements(int x, struct list* head){
	struct list* tempHead = head;

	int noOfElements;
	while(tempHead != NULL){
		if(tempHead ->data == x){
			noOfElements++;
		}
		tempHead = tempHead -> next;	
	}
	return noOfElements;
}

void print_list(struct list* head)
	{
	struct list* p = head;
		while(p != NULL) {
			printf("%d", p->data);
			getchar();
			p = p->next;
		}
	}
void add_sorted(int x, struct list* head){
	//keeping track of the pointer of previous element

	struct list* previousPointer = NULL;

	//creating a node with the data
	struct list* newNode = (struct list*)malloc(sizeof(struct list));
	newNode -> data = x;
	//Checking if list is empty
	if(head == NULL){
		head = newNode;
		newNode -> next = NULL;
	}
	//if list isn't empty

	struct list* tempHead = head;
	while(tempHead != NULL){
		//if x is bigger, continue searching
		if(x > tempHead -> data){
			//if there is no next element, insert x at tail
			if(tempHead -> next == NULL){
				tempHead -> next = newNode;
				newNode -> next = NULL;
				return;
			}
			//if there is another element, continue to another loop
			
			
		}
		//else x is not bigger - insert before
		else if(x <= tempHead -> data){
			//if there was a node previously
			if(previousPointer != NULL){
				previousPointer -> next = newNode;
			}

			//if there wasn't, set head to newNode
			else{
				head = newNode;
				//printf("We in this branchg");
			}
			newNode -> next = tempHead;
			return;
		}
		
		//at the end, update the address of last pointer
		previousPointer = tempHead;
		tempHead = tempHead -> next;
	}
	
}


int main(){
	//initiating a simple

	struct list* myHead;
	myHead = (struct list*)malloc(sizeof(struct list)); 
	struct list* startPointer = myHead;

	myHead -> data = 3;
	myHead -> next = (struct list*)malloc(sizeof(struct list));
	myHead = myHead -> next;

	myHead -> data = 4;
	myHead -> next = (struct list*)malloc(sizeof(struct list));
	myHead = myHead -> next;

	myHead -> data = 6;
	myHead -> next = NULL;
	


	add_sorted(-1, startPointer);
	add_sorted(8, startPointer);
	add_sorted(6, startPointer);
	add_sorted(5, startPointer);
	add_sorted(3, startPointer);
	add_sorted(0, startPointer);
	add_sorted(-2, startPointer);
	print_list(startPointer);
	
	printf("---\nNo of sixes: %d", count_elements(6, startPointer));

	

	
	
	
	return 0;
	
}