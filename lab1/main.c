#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>

int main()
{
	long int ttime;
	int code = 0;	//waiting mode (1 - defaut wait | 0 - manual wait) 
	long int st = time(NULL); //time(null) -- current time
	pid_t pid = fork(); //if pid = 0 => child procc, pid > 0 => parent procc, pid = -1 => error
	ttime = time(NULL);
	int rv;
	if(pid == 0) //child procc
	{
		printf("CHILD: my pid %x [%ld]\n", getpid(), time(&ttime)-st);
		printf("CHILD: parent pid %x\n", getppid());
		printf("CHILD: enter err code: \n");
		scanf("%d", &rv);
		printf("CHILD: my pid %x [%ld], bye\n", getpid(), time(&ttime)-st);
		exit(rv);
	}
	else //parent procc
	{
		printf("PARENT: my pid %x [%ld]\n", getpid(), time(&ttime)-st);
		printf("PARENT: my child pid %x \n", pid);
		
		if (code)
		{	
			waitpid(pid, &rv, WUNTRACED); //
		}else
		{
			while(0==waitpid(pid, &rv, WNOHANG))
			{
				sleep(1);
				printf(".");
			}
		}
		printf("PARENT: child's exit code: %d [%ld]\n", WEXITSTATUS(rv), time(&ttime)-st);
	}
	return 0;
}
