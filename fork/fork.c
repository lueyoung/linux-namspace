#include <unistd.h>
#include <stdio.h>

int main(){
    pid_t fpid;
    fpid = fork();
    if (fpid < 0){
        printf("error in fork!\n");
    } else if (fpid == 0) {
        printf("in child, process id is %d\n", getpid());
    } else {
        printf("in main, process id is %d\n", getpid());
    }
    return 0;
}
