#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>
#include <stdbool.h>

#define USER_SIG1 (SIGRTMIN)
#define USER_SIG2 (SIGRTMIN + 1)

#define PRINT_M1(X) printf("Rodzic  wyslal   sygnal. %i/%i\n", X, L)
#define PRINT_M2() printf("Rodzic  wyslal   sygnal koncowy.\n")
#define PRINT_M3(X) printf("Rodzic  odebral  sygnal. %i/%i\n", X, L)

void validate_args(int argc, char *argv[]);
void set_signals(struct sigaction *act);
void close_program(int v);
void setup_v1_signals(struct sigaction *act);
void send_sig1_async(int v, siginfo_t *info, void *ucont);
void setup_v2_signals(struct sigaction *act);
void send_sig1_sync(int v, siginfo_t *info, void *ucont);
void setup_v3_signals(struct sigaction *act);
void fsig2(int v, siginfo_t *info, void *ucont);
void run_child_process();
void send_async_signals_to_child();
void send_sync_signals_to_child();
void send_real_time_signals_to_child();
int isNumber(char *string);

int L;
int L2 = 0;
int Type;
int pid = 0;

int main(int argc, char *argv[])
{
    validate_args(argc, argv);

    L = atoi(argv[1]);
    Type = atoi(argv[2]);
    struct sigaction act;

    set_signals(&act);
    run_child_process();

    if (Type == 1)
    {
        send_async_signals_to_child();
    }
    else if (Type == 2 && L > 0)
    {
        send_sync_signals_to_child();
    }
    else if (Type == 3)
    {
        send_real_time_signals_to_child();
    }
}

void validate_args(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid args number. Expected 3, given %d!\n", argc - 1);
        exit(-1);
    }

    if (!isNumber(argv[1]) || !isNumber(argv[2]))
    {
        printf("Arguments should be numbers\n");
        exit(-1);
    }
}

void set_signals(struct sigaction *act)
{
    switch (Type)
    {
    case 1:
        setup_v1_signals(act);
        break;
    case 2:
        setup_v2_signals(act);
        break;
    case 3:
        setup_v3_signals(act);
        break;
    }
    act->sa_flags = 0;
    act->sa_handler = close_program;
    sigaction(SIGINT, act, NULL);
}

void close_program(int v)
{
    if (pid != 0)
        kill(pid, SIGKILL);
    exit(0);
}

void setup_v1_signals(struct sigaction *act)
{
    act->sa_sigaction = send_sig1_async;
    sigemptyset(&act->sa_mask);
    act->sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, act, NULL);
}

void send_sig1_async(int v, siginfo_t *info, void *ucont)
{
    L2++;
    PRINT_M3(L2);
}

void setup_v2_signals(struct sigaction *act)
{
    act->sa_sigaction = send_sig1_sync;
    sigemptyset(&act->sa_mask);
    act->sa_flags = SA_SIGINFO;
    sigaction(SIGUSR1, act, NULL);
}

void send_sig1_sync(int v, siginfo_t *info, void *ucont)
{
    L2++;
    PRINT_M3(L2);
    if (L2 == L)
    {
        PRINT_M2();
        kill(pid, SIGUSR2);
        exit(0);
    }
    else
    {
        PRINT_M1(L2 + 1);
        kill(pid, SIGUSR1);
    }
}

void setup_v3_signals(struct sigaction *act)
{
    act->sa_sigaction = fsig2;
    sigemptyset(&act->sa_mask);
    act->sa_flags = SA_SIGINFO;
    sigaction(USER_SIG1, act, NULL);
}

void fsig2(int v, siginfo_t *info, void *ucont)
{
    L2++;
    PRINT_M3(L2);
}

void run_child_process()
{
    if (!(pid = fork()))
    {
        execl("./child", "./child", NULL);
    }
    sleep(1);
}

void send_async_signals_to_child()
{
    for (int i = 0; i < L; ++i)
    {
        PRINT_M1(i + 1);
        // sending SIGUSR1 signal to child with kill command
        kill(pid, SIGUSR1);
    }
    PRINT_M2();
    kill(pid, SIGUSR2);
}

void send_sync_signals_to_child()
{
    PRINT_M1(1);
    // sending SIGUSR1 signal to child with kill command
    kill(pid, SIGUSR1);
    // wait for child response
    while (true)
        pause();
}

void send_real_time_signals_to_child()
{
    for (int i = 0; i < L; ++i)
    {
        PRINT_M1(i + 1);
        kill(pid, USER_SIG1);
    }
    PRINT_M2();
    kill(pid, USER_SIG2);
}

int isNumber(char *string)
{
    int n;
    int value;
    char c;
    n = sscanf(string, "%d%c", &value, &c);
    if (n != 1)
        return 0;
    return 1;
}