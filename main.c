#include <stdlib.h> 
#include "buffer.h"

buffer_item buffer[BUFFER_SIZE];

int main(int argc, char *argv[]) {
	/* 1. Get command line arguments argv[1],argv[2],argv[3] */
	/* 2. Initialize buffer */
	/* 3. Create producer thread(s) */
	/* 4. Create consumer thread(s) */
	/* 5. Sleep */
	/* 6. Exit */
}

int insert_item(buffer_item item) {
	/* insert item into buffer
	return 0 if successful, otherwise
	return -1 indicating an error condition */
}

int remove_item(buffer_item *item) {
	/* remove an object from buffer
	placing it in item
	return 0 if successful, otherwise
	return -1 indicating an error condition */
}

void *producer(void *param) {
	buffer_item item;
	while (true) {
		/* sleep for a random period of time */
		sleep(...);
		/* generate a random number */
		item = rand();
		if (insert_item(item))
		fprintf("report error condition");
		else
		printf("producer produced %d\n",item);
	}
}

void *consumer(void *param) {
	buffer_item item;
	while (true) {
		/* sleep for a random period of time */
		sleep(...);
		if (remove_item(&item))
		fprintf("report error condition");
		else
		printf("consumer consumed %d\n",item);
	}	
}