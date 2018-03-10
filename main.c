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
int timeToExit, pros, cons, i, run;
// pthread_mutex_lock(&mutex);
// pthread_mutex_unlock(&mutex);

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
	}	
	pthread_exit(0);
}

int main(int argc, char *argv[]) {
	i = 0;
	/* 1. Get command line arguments argv[1],argv[2],argv[3] */
	timeToExit = atoi(argv[1]);
	pros = atoi(argv[2]);
	cons = atoi(argv[3]);
	/* 2. Initialize buffer */
	sem_init(&full, 0, BUFFER_SIZE);
	sem_init(&empty, 0, 0);
	pthread_mutex_init(&mutex, NULL);
	/* 3. Create producer thread(s) */
	pthread_t producers[pros];
	int x;
	for (x = 0; x < pros; x++){
		pthread_create(&producers[x], NULL, producer, 0);
	}
	 // 4. Create consumer thread(s) 
	pthread_t consumers[cons];
	int y;
	for (y = 0; y < cons; y++){
		pthread_create(&consumers[y], NULL, consumer, 0);
	}
	/* 5. Sleep */
	
	sleep(timeToExit);
	run = 0;
	/* 6. Exit */

	for (x = 0; x < pros; x++)
		pthread_join(producers[x], NULL);

	for (y = 0; y < cons; y++)
		pthread_join(consumers[y], NULL);

	pthread_mutex_destroy(&mutex);
	sem_destroy(&full);
	sem_destroy(&empty);

	return 0;
}