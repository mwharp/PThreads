/*
 * A pthread program illustrating how to
 * create a simple thread and some of the pthread API
 * This program implements the summation function where
 * the summation operation is run as a separate thread.
 *
 * Most Unix/Linux/OS X users
 * gcc thrd.c -lpthread
 *
 * Figure 4.11
 *
 * @author Gagne, Galvin, Silberschatz
 * Operating System Concepts  - Tenth Edition
 * Copyright John Wiley & Sons - 2018
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct element{
	int data;
	struct element *next;
};
//a pointer to the head of the list

struct element *head;

// a temporary pointer used for freeing memory

struct element *temp; 

int sum; /* this data is shared by the thread(s) */

int n =5;

struct element *node;

//malloc allocates the memory to hold a struct element
void *runner(void *param); /* the thread */

int main(int argc, char *argv[])
{
pthread_t tid; /* the thread identifier */
pthread_attr_t attr; /* set of attributes for the thread */



//TRAVERSE THE LIST


if (argc != 2) {
	fprintf(stderr,"usage: a.out <integer value>\n");
	/*exit(1);*/
	return -1;
}

if (atoi(argv[1]) < 0) {
	fprintf(stderr,"Argument %d must be non-negative\n",atoi(argv[1]));
	/*exit(1);*/
	return -1;
}

/* get the default attributes */
pthread_attr_init(&attr);

/* create the thread */
pthread_create(&tid,&attr,runner,argv[1]);

/* now wait for the thread to exit */
pthread_join(tid,NULL);

while(head->next != NULL) {
	printf("%d\n",head->data);

	temp = head;
	head = head->next;
	free(temp);
	}
}

/**
 * The thread will begin control in this function
 */
void *runner(void *param) 
{
int i, upper = atoi(param);
  node = (struct element *) malloc(sizeof(struct element));
  sum = 0;
  node->data=upper;
  node->next = (struct element *) malloc(sizeof(struct element));
  node=node->next;
  head = node;
  printf("%d\n", upper);

	while(upper != 1) {
		if(upper%2 ==0){
			upper = upper/2;
		}else{
			upper=3*upper+1;
	   }
	node->data=upper;
	node->next = (struct element *) malloc(sizeof(struct element));
	node = node->next;
	printf("%d\n",upper);
	}

	pthread_exit(0);
}

