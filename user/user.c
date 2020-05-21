#define _GNU_SOURCE
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sched.h>
#include <signal.h>
#include <unistd.h>
#include <sys/capability.h>

#define STACK_SZIE (1024*1024)

static char child_stack[STACK_SZIE];
char* const child_args[] = {
    "/bin/bash",
    NULL
};

int child_main(void* args){
    printf("in container!\n");
    //cap_t caps;
    printf("eUID = %ld; eGID = %ld; ", (long) geteuid(), (long) getegid());
    //caps = cap_get_proc();
    //printf("capabilities: %s\n", cap_to_text(caps, NULL));
    sethostname("NewNamespace", 12);
    execv(child_args[0], child_args);
    return 0;
}

int main(){
    printf("starting...\n");
    int child_pid = clone(child_main, child_stack + STACK_SZIE, CLONE_NEWUSER | CLONE_NEWNET | CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWIPC | CLONE_NEWUTS | SIGCHLD, NULL);
    //int child_pid = clone(child_main, child_stack + STACK_SZIE, CLONE_NEWUSER | CLONE_NEWNET | CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWIPC | CLONE_NEWUTS | SIGCHLD, NULL);
    //int child_pid = clone(child_main, child_stack + STACK_SZIE, CLONE_NEWUSER | SIGCHLD, NULL);
    waitpid(child_pid, NULL, 0);
    printf("exit container\n");
    return 0;
}
