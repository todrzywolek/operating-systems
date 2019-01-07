#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void func_stop();
void func_term();

bool work = true;

int main(int argc, char *argv[])
{
    struct sigaction act;
    act.sa_handler = func_term;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;

    sigaction(SIGINT, &act, NULL);
    signal(SIGTSTP, func_stop);
    
    while (1)
    {
        if (work)
            print_time();
        sleep(1);
    }
}

void func_stop()
{
    if (work)
    {
        printf("Wywolano SIGTSTP!\n");
        printf("Oczekuje na CTRL+Z - kontynuacja albo CTR+C - zakonczenie programu\n");
        work = false;
    }
    else
        work = true;
}

void func_term()
{
    printf("Odebrano sygnal SIGINT!\n");
    exit(0);
}

void print_time()
{
    const time_t g = time(NULL);
    struct tm *curtime = localtime(&g);
    printf("%d:%d:%d\n", curtime->tm_hour, curtime->tm_min, curtime->tm_sec);
}