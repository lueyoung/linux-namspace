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
    sethostname("NewNamespace", 12);
    char* mount_point = "/proc";
    mkdir(mount_point, 0555);
    if (mount("proc", mount_point, "proc", 0, NULL) == -1){
        printf("error when mount!\n");
    }
    pid_t pid = fork();
    if (pid == 0) {
        execv(child_args[0], child_args);
    } else {
        wait(NULL);
    }
    return 0;
}

int main(){
    printf("starting...\n");
    //int child_pid = clone(child_main, child_stack + STACK_SZIE, SIGCHLD, NULL);
    int child_pid = clone(child_main, child_stack + STACK_SZIE, CLONE_NEWPID | CLONE_NEWIPC | CLONE_NEWUTS | CLONE_NEWNS | SIGCHLD, NULL);
    waitpid(child_pid, NULL, 0);
    printf("end\n");
    return 0;
}
