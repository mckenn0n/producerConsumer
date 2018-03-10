#include <stdlib.h> 
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include "buffer.h"

buffer_item buffer[BUFFER_SIZE];
pthread_mutex_t mutex;
sem_t empty;
sem_t full;
int timeToExit, pros, cons, i, run, p, c, pp, cc;
int insert_item(buffer_item item) {
	if (i < BUFFER_SIZE){
		buffer[i++] = item;
	} else{
		printf("Something went wrong while inserting an item.\nIndex is %d\n", i);
		return -1;
	} 
	return 0;
}

int remove_item() {
	if (i > 0){
		return buffer[--i];
	} else{
		printf("Something went wrong while trying to remove an item.\nIndex is %d\n", i);
		return -1;
	}
	return 0;
}

void *producer(void *param) {
	buffer_item item;
	run = 1;
	while (run) {
		sleep(rand() % 10);
		item = rand();
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		if (insert_item(item) == -1)
		printf("Report error condition PRODUCER");
		else
		printf("Producer produced %d\n",item);
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
		p++;
	}
	pthread_exit(0);
}

void *consumer(void *param) {
	buffer_item item;
	run = 1;
	while (run) {
		sleep(rand() % 10);
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		item = remove_item();
		if (item == -1)
		printf("Report error condition CONSUMER");
		else
		printf("Consumer consumed %d\n",item);
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
		c++;
	}	
	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	if(argc != 4){
		printf("Wrong number of command line arguments.\n");
		exit(0);
	}
	i, c, p, cc, pp= 0;
	timeToExit = atoi(argv[1]);
	pros = atoi(argv[2]);
	cons = atoi(argv[3]);
	
	sem_init(&full, 0, BUFFER_SIZE);
	sem_init(&empty, 0, 0);
	pthread_mutex_init(&mutex, NULL);
	
	pthread_t producers[pros];
	int x;
	for (x = 0; x < pros; x++){
		pthread_create(&producers[x], NULL, producer, 0);
		pp++;
	}
	
	pthread_t consumers[cons];
	int y;
	for (y = 0; y < cons; y++){
		pthread_create(&consumers[y], NULL, consumer, 0);
		cc++;
	}
	
	printf("\t!!!Creating threads for %d seconds!!!\n", timeToExit);
	sleep(timeToExit);
	run = 0;
	printf("\tWaiting on all threads to exit. Program will end soon.\n");
	printf("\tJoining producers.\n");
	for (x = 0; x < pros; x++){
		pthread_join(producers[x], NULL);
		if(pp == p){
			break;
		}
	}
	printf("\tAll producer threads exited.\n");

	printf("\tJoining consumers.\n");
	for (y = 0; y < cons; y++){
		pthread_join(consumers[y], NULL);
		if(c == cc){
			break;
		}
	}
	printf("\tAll consumer threads exited.\n");

	pthread_mutex_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);

	return 0;
}