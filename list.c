#include <stdio.h>
#include <stdlib.h>
#include "list.h"

void list_print(const struct node *list) {
    int i = 0;
    printf("In list_print\n");
    while (list != NULL) {
        printf("List item %d: %d\n", i+1, list->value);
        list = list->next;
	i++;
    }
}


void list_append(int value, struct node **head) {
    
    struct node *appendnode = malloc(sizeof(struct node));
    appendnode -> value = value;
    appendnode -> next = NULL;
    if (*head == NULL) {
	*head = appendnode;
    }
    
    else {
	struct node *tempnode = *head;
	while (tempnode -> next != NULL){
	    tempnode = tempnode -> next;
	}
	tempnode -> next = appendnode;
    }
}



void list_sort(struct node **head) {
    struct node *countnode = *head;
    int count = 0;
    while (countnode != NULL) {
	count++;
	countnode = countnode -> next;
    }

    struct node *first = NULL;
    struct node *second = NULL;

    for(int i = 0; i < count; i++) {
	first = *head;
	if (first -> next != NULL) {
	    second = first -> next;
	}
	else {
	    second = NULL;
	}

	while (second != NULL) {
	    if ((first -> value) > (second -> value)) {
		int firstval = first -> value;
		int secondval = second -> value;
		first -> value = secondval;
		second -> value = firstval;
	    }
	    first = second;
	    second = second -> next;
	}
    }
}



void list_destroy(struct node **head) {
    struct node *list = *head;
    struct node *temp;
    while (list != NULL) {
	temp = list -> next;
	free(list);
	list = temp;
    }
}

















