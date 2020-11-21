#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 1000000
long long counter = 0;

static sem_t sem;

void* counting_thread(void* arg) {
	int offset = *(int*) arg;
	int i;
	for(i = 0; i < N; i++){
        sem_wait(&sem);
		counter += offset;
        sem_post(&sem);
	}
	pthread_exit(NULL);
}

int main() {
    sem_init(&sem, 0, 1);
	pthread_t th1;
	int offset1 = 1;
	pthread_create(&th1, NULL, counting_thread, (void*) &offset1);

	pthread_t th2;
    int offset2 = -1;
	pthread_create(&th2, NULL, counting_thread, (void*) &offset2);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);

	printf("Final counter value: %lld\n", counter);
    sem_destroy(&sem);
	return 0;
} 

