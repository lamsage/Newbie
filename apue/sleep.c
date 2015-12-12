#include "apue.h"
#include <setjmp.h>
#include <signal.h>
#include <unistd.h>

static jmp_buf env_alrm;

static void sig_alrm(int signo){
	longjmp(env_alrm, 1);
}

unsigned int sleep(unsigned int nsecs){
	if(signal(SIGALRM, sig_alrm) == SIG_ERR)
		return (nsecs);
	if(setjmp(env_alrm) == 0){
		alarm(nsecs);
		pause();
	}
	return (alarm(0));
}

static void sig_int(int);

int main(void) {
	unsigned int unslept;
	if(signal(SIGINT, sig_int) == SIG_ERR)
		err_sys("signal(SIGINT) error\n");
	unslept = sleep(5);
	printf("sleep return: %u\n", unslept);
	exit(0);
}

static void sig_int(int signo){
	int i,j;
	int k;
	printf("\nsig_int starting\n");
	for( i = 0; i < 300000; i++)
		for( j = 0; j < 4000; j++)
			k += i * j;
	printf("sig_itn finished\n");
}
