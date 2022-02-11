#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signum, siginfo_t *info , void *context)
{
    printf("Recu signal %d par PID %d\n", signum, info->si_pid);
}

int main(int argc, char ** argv)
{
    struct sigaction action;

    action.sa_flags = SA_SIGINFO;
    action.sa_sigaction = handler;
    sigemptyset(&action.sa_mask);
    sigaction(SIGINT, &action, NULL);
    while (1)
        pause();
    return (1);
}