#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <execinfo.h>                                                                                            
#include <signal.h> 

void stack_dump(int signo, struct siginfo* siginfo, void* myact)
{
	printf("\n ***** start dump *****\n");
	void*array[30];

	size_t size;char**strings;
	size_t i;
	size = backtrace(array,30);
	strings = backtrace_symbols(array, size);
	printf ("Obtained %zd stack frames. The signo = %d\n", size, signo);
	printf("Current address:%X\n\n", siginfo->si_addr);
	for(i =0; i < size; i++)
		printf ("%s \n", strings[i]);
	free (strings);

	printf("\n ***** end dump *****\n");
	while(1);
}

void init_dump(void) 
{
	printf("Init_dump now\n");
	struct sigaction act;
	sigemptyset(&act.sa_mask);
	act.sa_flags=SA_SIGINFO;
	act.sa_sigaction=stack_dump;
	sigaction(SIGILL, &act, NULL);
	sigaction(SIGABRT, &act, NULL);
	sigaction(SIGBUS, &act, NULL);
	sigaction(SIGFPE, &act, NULL);
	sigaction(SIGSEGV, &act, NULL);
	sigaction(SIGPIPE, &act, NULL);
	sigaction(SIGKILL, &act, NULL);
}

