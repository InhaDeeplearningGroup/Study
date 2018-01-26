#include <stdlib.h>
#include <stdio.h>
#include <sched.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/resource.h>

#define ITERATIONS 77777777

void SP() {
	int which;
	which = sched_getscheduler(0);
	switch (which) {
	case SCHED_OTHER:
		printf("[INFO] Default Scheduling\n");
		break;
	case SCHED_FIFO:
		printf("[INFO] FIFO Scheduling\n");
		break;
	case SCHED_RR:
		printf("[INFO] RR Scheduling\n");
		break;
	}
}


int main() {
	int sched_setscheduler (pid_t pid, int policy, const struct sched_param *p);
	int sched_getscheduler (pid_t pid);
	int gtrusage (int who, struct rusage *usage);
	struct sched_param p;

		struct rusage usage;
		int i;
		int A[1000000];

		SP();
		p.sched_priority = 1;

		if (sched_setscheduler(0, SCHED_FIFO, &p) != 0) {
			printf("[INFO] Failed to set the scheduler \n");
		}
		SP();


		for (i=0; i<ITERATIONS; i++)
			A[i & 999999] = lrand48();
		sched_yield();

		for (i=0; i<ITERATIONS; i++)
			A[i & 243561] = lrand48();
		sched_yield();

		for (i=0; i<ITERATIONS; i++)
			A[i & 456456] = lrand48();
		sched_yield();

		for (i=0; i<ITERATIONS; i++)
			A[i & 756121] = lrand48();
		sched_yield();

		gtrusage(RUSAGE_SELF, &usage);
		printf("[INFO] No. of voluntary switches = %ld \n", usage.ru_nvcsw);
		printf("[INFO] No. of involuntary switches = %ld \n", usage.ru_nivcsw);
		printf("[INFO] No. of page faults = %ld \n", usage.ru_majflt);

		exit(0);
}
