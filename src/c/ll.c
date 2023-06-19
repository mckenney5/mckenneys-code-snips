/* Singley + Double Linked List */

#include <stdio.h>
#include <stdlib.h>

struct SingleLinkedList {
	int data;
	void *next;
};

struct DoubleLinkedList {
	int data;
	void *next;
	void *prev;
};

void traverse_dll(struct DoubleLinkedList *head_ptr){
	// Traverses the linked list, freeing as we go
	size_t count = 0;
	void *temp = NULL;
	
	do {
		printf("[%03ld] \tData: '%d' \tNext: %#011x \tPrev: %#011x\n", count++, head_ptr->data, head_ptr->next, head_ptr->prev);
		temp = head_ptr;
		head_ptr = head_ptr->next;
		free(temp);

	} while(head_ptr != NULL);
	printf("\n\n");
}

void traverse_sll(struct SingleLinkedList *head_ptr){
	// Traverses the linked list, freeing as we go
	size_t count = 0;
	void *temp = NULL;

	do {
		printf("[%03ld] \tData: '%d' \tNext: %#011x\n", count++, head_ptr->data, head_ptr->next);
		temp = head_ptr;
		head_ptr = head_ptr->next;
		free(temp);

	} while(head_ptr != NULL);
	printf("\n\n");
}

struct DoubleLinkedList *gen_dll(const size_t ammount){
	// Allocates a double linked list, must be free'd
	struct DoubleLinkedList *ptr = NULL; //pointer to lists
	struct DoubleLinkedList *previous = NULL;
	struct DoubleLinkedList *head = NULL;
	size_t i = 0;
	
	ptr = (struct DoubleLinkedList *)malloc(sizeof(struct DoubleLinkedList));
	if(ptr == NULL) exit(1);
	head = ptr; //sets the head, this is what we will return

	for(i = 0; i < ammount; i++){
		printf("%d...", i + 1);
		// initalize data
		ptr->data = i;
		ptr->prev = previous;
		if(i + 1 < ammount){
			ptr->next = (struct DoubleLinkedList *)malloc(sizeof(struct DoubleLinkedList));
			if(ptr->next == NULL) exit(1);

			// move to next list
			previous = ptr;
			ptr = ptr->next;
		}
		else	//if this is the last one
			ptr->next = NULL;
	}
	printf("done\n\n");
	return head;
}

struct SingleLinkedList *gen_sll(const size_t ammount){
	// Allocates a double linked list, must be free'd
	struct SingleLinkedList *ptr = NULL; //pointer to lists
	struct SingleLinkedList *head = NULL;
	size_t i = 0;
	
	ptr = (struct SingleLinkedList *)malloc(sizeof(struct SingleLinkedList));
	if(ptr == NULL) exit(1);
	head = ptr; //sets the head, this is what we will return

	for(i = 0; i < ammount; i++){
		printf("%d...", i + 1);
		// initalize data
		ptr->data = i;
		if(i + 1 < ammount){
			ptr->next = (struct SingleLinkedList *)malloc(sizeof(struct SingleLinkedList));
			if(ptr->next == NULL) exit(1);

			// move to next list
			ptr = ptr->next;
		}
		else	//if this is the last one
			ptr->next = NULL;
	}
	printf("done\n\n");
	return head;
}

int main(int argc, char *argv[]){
	long long ammount = 5, i = 0;
	if(argc == 2)
		ammount = atol(argv[1]);

	if(ammount <= 0) return 2;

	printf("-- Generating %lld Double Linked List of size %lld bytes --\n", ammount, sizeof(struct DoubleLinkedList));
	void *ptr = gen_dll((size_t)ammount);
		
	printf("-- Traversing Double LL --\n");
	traverse_dll((struct DoubleLinkedList*) ptr);

	printf("-- Generating %lld Single Linked List of size %lld bytes --\n", ammount, sizeof(struct SingleLinkedList));
	ptr = gen_sll((size_t)ammount);

	printf("-- Traversing Single LL --\n");
	traverse_sll((struct SingleLinkedList*) ptr);

	return 0;
}
