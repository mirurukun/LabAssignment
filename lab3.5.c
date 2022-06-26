#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int getNumber(){

int number;

	printf("\nEnter any number : ");
	scanf("%d", &number);
	return number;
}

int main(void) {

  int fd[2];
  pipe(fd);
  pid_t pid = fork();
  void sigint_handler(int sig);

  if(signal(SIGINT, sigint_handler) == SIG_ERR){
     perror("signal");
     exit(1);
    }

  if(pid > 0) {
    wait(NULL);
    close(0);
    close(fd[1]);
    dup(fd[0]);

    int i, nombor = 0;
    read(fd[0], &nombor, sizeof(nombor));

    if (nombor == 0 || nombor == 1)
       { printf("\n%d is not prime number\n",nombor); }

   for (i = 2; i <= nombor / 2; ++i) {

        // if n is divisible by i, then n is not prime
         if (nombor % i == 0) {
             printf("\n%d is not prime number\n",nombor);
             break;
             }
         else
             { printf("\n%d is prime number\n",nombor);
               break;
             }
    }

    }

   else if(pid == 0) {
    dup(fd[1]);

    int number = getNumber();
    write(fd[1], &number, sizeof(number));
    close(fd[0]);
    close(1);

    exit(EXIT_SUCCESS);
  }



return EXIT_SUCCESS;
}


void sigint_handler(int sig){
  printf("SIGINT signal\n");
}