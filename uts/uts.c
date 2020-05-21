#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>

#define STACK_SZIE (1024*1024)

static char child_stack[STACK_SZIE];
char* const child_args[] = {
    "/bin/bash",
    NULL
};

int child_main(void* args){
    printf("in child process!\n");
    execv(child_args[0], child_args);
    return 1;
}

int main(){
    printf("starting...\n");
    int child_pid = clone(child_main, child_stack + STACK_SZIE, SIGCHLD, NULL);
    waitpid(child_pid, NULL, 0);
    printf("end\n");
    return 0;
}
