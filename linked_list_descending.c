#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
typedef struct node{
	int name;
	char extra[100];
	int expire_time;
	node *next = NULL;
}Node;

typedef struct list{
    node *first_node;
}List;

/*create new list*/
List* new_list(void);
/*insert new node at head of list*/
void list_insert_begin(List *list, int expire_time, int name);
/*insert new node after selected node*/
void node_insert_after(Node *node, int expire_time, int name);
/*insert node depend on expire time*/
void node_insert_ordered(List *list, int expire_time, int name);
/*search expire node*/
void search_expired_from(List *list,int stime);
/*remove first node of list*/
void node_remove_begin(List *list);
/*remove node after selected node*/
void node_remove_after(Node *node);
/*remove every node when it's less than expire_time*/
void  node_remove_from(List *list,int expire_time);
/*print every node in list*/
void print_list(List *list);
/*print from selected node to last node*/
void print_node_to_end(Node *node);

int main(int argc, char const *argv[])
{
	int j;
	List *list = new_list();
	list->first_node->expire_time =0;
	// list->first_node->expire_time = (unsigned)time(NULL);
	list->first_node->name = 0;

	for (int i = 1; i < 10000001; ++i)
	{
		// j = rand() % 101;
		// node_insert_ordered(list, (unsigned)time(NULL)-j, i);
		node_insert_ordered(list, i, i);		
		// if(i % 10000 == 0){
		// 	node_remove_from(list,(unsigned)time(NULL)-9);
		// }
	}
	//print_list(list);

	return 0;
}

List* new_list(void){
	List *list = (List *) malloc(sizeof(node));
	list->first_node = new(Node);
	return list;
}
	
void list_insert_begin(List *list, int expire_time, int name){
	Node *new_node = new(Node);
	new_node->expire_time = expire_time;
	new_node->name = name;
	new_node->next = list->first_node;
	list->first_node = new_node;
}

void node_insert_after(Node *node, int expire_time, int name){
	Node *new_node = new(Node);
	new_node->expire_time = expire_time;
	new_node->name = name;
	new_node->next = node->next;
	node->next = new_node;
}

void node_insert_ordered(List *list, int expire_time, int name){

	if (list->first_node->expire_time < expire_time){
		list_insert_begin(list, expire_time, name);
	}
	else if(list->first_node->expire_time > expire_time && list->first_node->next == NULL){
		node_insert_after(list->first_node, expire_time, name);
	}
	else{
		Node *node = list->first_node->next;
		Node *prev_node = list->first_node;

	 	while (node != NULL){
	 		if(node->expire_time < expire_time){
	 			node_insert_after(prev_node, expire_time, name);
	 			break;
	 		}
	 		prev_node = node; 
	 		node = node->next;

	 	}
	 	if(node == NULL){
	 		node_insert_after(prev_node, expire_time, name);
	 	}
	}
}

void search_expired_from(List *list,int stime){
	Node *node = list->first_node;
	while (node != NULL && node->expire_time > stime){
 		node = node->next;

	}
	if(node == NULL){
		printf("Don't have expired Data.\n");
	}else print_node_to_end(node);
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

/*remove every node when it's less than expire_time*/
void  node_remove_from(List *list,int expire_time){
	Node *node = list->first_node;
	Node *next = list->first_node->next;
	while (next->expire_time > expire_time){
 		node = next;
 		next = next->next;
	}
	node->next = NULL;
	node = next;
	next = next->next;
	while (next != NULL){
 		delete node;

 		node = next;
 		next = next->next;
 	}
 	delete node;
}

void print_list(List *list){
	Node *node = list->first_node;
 	while (node != NULL){
 		printf("%d:%d",node->name, node->expire_time);
 		printf("->");
 		node = node->next;
 	}
 	printf("NULL\n");
}

void print_node_to_end(Node *node){
 	while (node != NULL){
 		printf("%d:%d",node->name, node->expire_time);
 		printf("->");
 		node = node->next;
 	}
 	printf("NULL\n");
}

