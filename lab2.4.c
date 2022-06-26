#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
void childProcess(){
        char name[100];
            for(int i=1; i<5; i++){
            printf("USER %d ENTER YOUR NAME: ", i);
            fgets(name, sizeof(name), stdin); 
            printf("USER %d :", i);
            puts(name); 
        }
}
void parentProcess(){
    printf("JOB IS DONE!\n");
}
int main(void){
    pid_t pid = fork();
        if(pid==0){
            childProcess();
            exit(EXIT_SUCCESS);
        }
        else if(pid > 0){
            wait(NULL);
            parentProcess();
        }
        return EXIT_SUCCESS;
}