#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define USER_SIG1 (SIGRTMIN)
#define USER_SIG2 (SIGRTMIN + 1)

void set_signal_handlers(struct sigaction *act);
void sig1_handler(int v, siginfo_t *info, void *ucont);
void sig2_handler(int v, siginfo_t *info, void *ucont);

int l = 0;

int main()
{
    struct sigaction act;

    set_signal_handlers(act);
    while (true)
        pause();
}

void set_signal_handlers(struct sigaction *act)
{
    act->sa_sigaction = sig1_handler;
    sigemptyset(&act->sa_mask);
    act->sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, act, NULL);
    sigaction(USER_SIG1, act, NULL);

    act->sa_sigaction = sig2_handler;
    sigaction(SIGUSR2, act, NULL);
    sigaction(USER_SIG2, act, NULL);
}

void sig1_handler(int v, siginfo_t *info, void *ucont)
{
    l++;
    printf("Dziecko odebralo sygnal. %i/?\n", l);
    kill(getppid(), info->si_signo);
}

void sig2_handler(int v, siginfo_t *info, void *ucont)
{
    printf("Dziecko odebralo sygnal zakonczenia.\n");
    exit(0);
}