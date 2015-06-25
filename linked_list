#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct node{
	int data;
	node *next = NULL;
}Node;

typedef struct list{
    node *first_node;
}List;

List* new_list(void){
	List *list = (List *) malloc(sizeof(node));
	list->first_node = new(Node);
	return list;
}

void node_insert_begin(List *list, int data){
	Node *new_node = new(Node);
	new_node->data = data;
	new_node->next = list->first_node;
	list->first_node = new_node;
}

void node_insert_after(Node *node, int data){
	Node *new_node = new(Node);
	new_node->data = data;
	new_node->next = node->next;
	node->next = new_node;
}

void node_insert_ordered(List *list, int data){

	if (list->first_node->data > data){
		node_insert_begin(list, data);
	}
	else if(list->first_node->data < data && list->first_node->next == NULL){
		node_insert_after(list->first_node, data);
	}
	else{
		Node *node = list->first_node->next;
		Node *prev_node = list->first_node;

	 	while (node != NULL){
	 		if(node->data > data){
	 			node_insert_after(prev_node, data);
	 			break;
	 		}
	 		prev_node = node; 
	 		node = node->next;

	 	}
	 	if(node == NULL){
	 		node_insert_after(prev_node, data);
	 	}
	}
}

void node_remove_begin(List *list){
	Node *d_node = list->first_node;
	list->first_node = list->first_node->next;
	delete d_node;

}

void node_remove_after(Node *node){
	Node *d_node = node->next;
	node->next = node->next->next;
	delete d_node;
}

void print_list(List *list){
	Node *node = list->first_node;
 	while (node != NULL){
 		printf("%d", node->data);
 		printf("->");
 		node = node->next;
 	}
 	printf("NULL\n");
}

Node* last_node(List *list){

}



int main(int argc, char const *argv[])
{
	int j;
	List *list = new_list();
	list->first_node->data = 0;
	for (int i = 1; i < 100000; ++i)
	{
		j = rand() % 1000001;
		node_insert_ordered(list,j);
	}
	print_list(list);
	/*node_insert_after(list->first_node,10);
	node_remove_begin(list);
	print_list(list);
	Node *node = list->first_node;
 	while (node != NULL){
 		if(node->data == 7) node_remove_after(node);
 		node = node->next;
 	}
 	print_list(list);*/
	return 0;
}
