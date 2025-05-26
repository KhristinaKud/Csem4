#include <stdio.h>
#include <unistd.h>

int main() {
    int pid;
    pid = fork();
    if(pid < 0) {
        perror("fork failed");
        return 1;
    }
   else if(pid == 0) {
      printf("I am the child:%d\n",pid);
   }
   else{
     printf("I am the parent:%d\n",pid);
   }
    printf("%d\n", pid);
    return 0;
}