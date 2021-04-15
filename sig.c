#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ucontext.h>


void sig_handler(int signum){

  //Return type of the handler function should be void
  printf("\nFuck you I won't die!!!!!\n");

  char *nullptr = 0x200000;

  *nullptr = 0x0;
}

void sig_segv_handler(int signum, siginfo_t *info, void *ucontext){

  //Return type of the handler function should be void
  printf("\nOoops...your program just Seg Faulted @ %p\n", info->si_addr, ((ucontext_t*)ucontext)->uc_mcontext.gregs[REG_RIP]);
  exit(1);
}


int main(){
  struct sigaction sa;
  sa.sa_flags = SA_SIGINFO;
  sigemptyset (&sa.sa_mask);
  sa.sa_sigaction = &sig_segv_handler;
  if (sigaction(SIGSEGV, &sa, NULL) == -1) {
    fprintf(stderr, "failed to setup SIGSEGV handler\n");
    exit(1);
  }

  signal(SIGINT,sig_handler); // Register signal handler
  //signal(SIGSEGV,sig_segv_handler); // Register signal handler
  for(int i=1;;i++){    //Infinite loop
//    printf("%d : Inside main function\n",i);
    sleep(1);  // Delay for 1 second
  }
  return 0;
}
