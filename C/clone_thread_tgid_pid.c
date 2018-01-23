#define _GNU_SOURCE //important!!
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <linux/unistd.h>
#include <sched.h>
#include <sys/wait.h>

int print_function(void *arg) {
    printf("TGID(%d), PID(%d): Child \n", getpid(), syscall(__NR_gettid));
    sleep(5);
    return 0;
}

int main(void) {
    int pid;
    int child_a_stack[4096], child_b_stack[4096];

    printf("before clone \n \n");
    printf("TGID(%d), PID(%d): Parent \n", getpid(), syscall(__NR_gettid));

    clone(print_function, (void *)(child_a_stack+4095), CLONE_CHILD_CLEARTID | CLONE_CHILD_SETTID, NULL);
    clone(print_function, (void *)(child_b_stack+4095), CLONE_VM | CLONE_THREAD | CLONE_SIGHAND, NULL);

    sleep(5);

    printf("after clone \n \n");
    return 0;
}
/*
 before clone
 TGID(17746), PID(17746): Parent
 TGID(17747), PID(17747): Child
 TGID(17746), PID(17748): Child
 after clone
 */

