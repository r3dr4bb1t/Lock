#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

long g_count = 0;
int pshared;

static pthread_spinlock_t g_mutex;
struct timeval start, end;

void *thread_func(void *arg)
{
	long i, count = (long)arg;

	/*
	 * Increase the global variable, g_count.
	 * This code should be protected by
	 * some locks, e.g. spin lock, and the lock that 
	 * you implemented for assignment,
	 * because g_count is shared by other threads.
	 */
	for (i = 0; i<count; i++) {
		pthread_spin_lock(&g_mutex);
		g_count++;
		pthread_spin_unlock(&g_mutex);
		/******************************************/
	}
}

int main(int argc, char *argv[])
{
pthread_spin_init(&g_mutex,pshared);
	gettimeofday(&start, NULL);
	pthread_t *tid;
	long i, thread_count, value;
	int rc;

	/*
	 * Check that the program has three arguments
	 * If the number of arguments is not 3, terminate the process.
	 */
	if (3 != argc) {
		fprintf(stderr, "usage: %s <thread count> <value>\n", argv[0]);
		exit(0);
	}

	/*
	 * Get the values of the each arguments as a long type.
	 * It is better that use long type instead of int type,
	 * because sizeof(long) is same with sizeof(void*).
	 * It will be better when we pass argument to thread
	 * that will be created by this thread.
	 */
	thread_count = atol(argv[1]);
	value = atol(argv[2]);

	/*
	 * Create array to get tids of each threads that will
	 * be created by this thread.
	 */
	tid = (pthread_t*)malloc(sizeof(pthread_t)*thread_count);
	if (!tid) {
		fprintf(stderr, "malloc() error\n");
		exit(0);
	}

	/*
	 * Create a threads by the thread_count value received as
	 * an argument. Each threads will increase g_count for
	 * value times.
	 */
	for (i = 0; i<thread_count; i++) {
		rc = pthread_create(&tid[i], NULL, thread_func, (void*)value);
		if (rc) {
			fprintf(stderr, "pthread_create() error\n");
			free(tid);
			pthread_mutex_destroy(&g_mutex);
			exit(0);
		}
	}

	/*
	 * Wait until all the threads you created above are finished.
	 */
	for (i = 0; i<thread_count; i++) {
		rc = pthread_join(tid[i], NULL);
		if (rc) {
			fprintf(stderr, "pthread_join() error\n");
			free(tid);
			pthread_mutex_destroy(&g_mutex);
			exit(0);
		}
	}

	/*
	 * Print the value of g_count.
	 * It must be (thread_count * value)
	 */ 
	printf("value: %ld\n", g_count);

	free(tid);
	gettimeofday(&end,NULL);

  printf("Time in microseconds: %ld microseconds\n",
            ((end.tv_sec - start.tv_sec)*1000000L
           +end.tv_usec) - start.tv_usec);

}
