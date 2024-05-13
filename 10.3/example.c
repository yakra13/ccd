/*10.3 Demonstrate the ability to use the following constructs

Objectives

- [ ] Signal handling
- [ ] Interrupts
*/

#include <stdbool.h>
#include <stdio.h>
#include <signal.h>
#include <windows.h>

volatile sig_atomic_t eflag = 0;
char* info = NULL;

int count = 0;

void log_message()
{
    fputs(info, stderr);
}

void handle_sigint(int sig)
{
    signal(SIGINT, handle_sigint);
    
    (void)sig;
    printf("BLAH\n");

    eflag = -1;

    // count++;
    // printf("Control-C'ed %d time(s)\n", count);

    // if (count == 3)
    // {
    //     printf("Exiting...\n");
    //     exit(0);
    // }
}

void handle_sigsegv(int sig)
{
    signal(SIGSEGV, handle_sigsegv);
    (void)sig;

    printf("Segmentation fault detected.\n");

    // printf("Exiting...\n");
    // exit(0);
}

int main(void)
{
    // signal(SIGINT, handle_sigint);
    // signal(SIGSEGV, handle_sigsegv);
    // int dummy = 0xDEADBEEF;
    // int* p_dummy = &dummy;
    // printf("Contents of memory %d\n", p_dummy[-10000]);

    if (signal(SIGINT, handle_sigint) == SIG_ERR)
    {
        printf("Pressed ctrl-c\n");
    }

    info = (char*)malloc(1024);
    
    if (info == NULL)
    {
        exit(1);
    }
    
    while (eflag != 1)
    {
        //log_message();
    }

    log_message();
    free(info);
    info = NULL;

    // while (true)
    // {
    //     printf("a");
    //     Sleep(3);
    // }

    return 0;
}