#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
typedef struct node{
	char name[256];
	int expire_time;
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

void node_insert_begin(List *list, int expire_time, char* name){
	Node *new_node = new(Node);
	new_node->expire_time = expire_time;
	new_node->next = list->first_node;
	list->first_node = new_node;
}

void node_insert_after(Node *node, int expire_time, char* name){
	Node *new_node = new(Node);
	new_node->expire_time = expire_time;
	new_node->next = node->next;
	node->next = new_node;
}

void node_insert_ordered(List *list, int expire_time, char* name){

	if (list->first_node->expire_time > expire_time){
		node_insert_begin(list, expire_time, name);
	}
	else if(list->first_node->expire_time < expire_time && list->first_node->next == NULL){
		node_insert_after(list->first_node, expire_time, name);
	}
	else{
		Node *node = list->first_node->next;
		Node *prev_node = list->first_node;

	 	while (node != NULL){
	 		if(node->expire_time > expire_time){
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
/*remove first node of list*/
void node_remove_begin(List *list){
	Node *d_node = list->first_node;
	list->first_node = list->first_node->next;
	delete d_node;

}

/*remove node after selected node*/
void node_remove_after(Node *node){
	Node *d_node = node->next;
	node->next = node->next->next;
	delete d_node;
}

/*remove from first node to specify value*/
void  node_remove_to(List *list,int expire_time){
	Node *node = list->first_node;
	Node *next = list->first_node->next;
	while (node != NULL){
 		if(node->expire_time > expire_time){
 			break;
 		}
 		else{
 			list->first_node = next;
 			delete node;
 		}
 		node = next;
 		next = next->next;
 	}

}

void print_list(List *list){
	Node *node = list->first_node;
 	while (node != NULL){
 		printf("%d", node->expire_time);
 		printf("->");
 		node = node->next;
 	}
 	printf("NULL\n");
}

char* get_utime(void){
	struct timeval tv;
	struct timezone tz;
	struct tm *tm;
	char *utime = (char*)malloc(16);
	gettimeofday(&tv, &tz);
	tm=localtime(&tv.tv_sec);
	sprintf(utime," %d%02d%02d%lu", tm->tm_hour, tm->tm_min,
		tm->tm_sec, tv.tv_usec);
	return utime;
}

int main(int argc, char const *argv[])
{
	char sname[] = "00000000";
	int j;
	List *list = new_list();
	list->first_node->expire_time = 0;
	for (int i = 1; i < 10000; ++i)
	{
		j = rand() % 10001;
		node_insert_ordered(list, j, sname);
	}
	//printf("%s\n",get_utime() );
	printf("%s\n", get_utime());
	// node_remove_to(list,3000);
	print_list(list);
	/*node_insert_after(list->first_node,10);
	node_remove_begin(list);
	print_list(list);
	Node *node = list->first_node;
 	while (node != NULL){
 		if(node->expire_time == 7) node_remove_after(node);
 		node = node->next;
 	}
 	print_list(list);*/
	return 0;
}
	

