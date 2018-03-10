This is a simple solution the the producer consumer problem using counting semaphores and a mutex lock.

Compile

	gcc main.c -lpthread

Run

	./a.out [time to create threads (int)] [number of producer threads (int)] [number of consumer threads (int)]

