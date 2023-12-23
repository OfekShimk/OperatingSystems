#include <signal.h>
#include <unistd.h>

int global_status;
sigset_t waitset;

void sem_init(int status) {
    global_status = status;
    sigemptyset(&waitset);
    sigaddset(&waitset, SIGUSR1);
    sigprocmask(SIG_BLOCK, &waitset, NULL);
}

void sem_down() {
    if (global_status == 0) {
        int sig = 0;
        
        while (sig != SIGUSR1) {
            sigwait(&waitset, &sig);
        }
    }
    global_status = 0;
}

void sem_up() {
    global_status = 1;
    kill(getpid(), SIGUSR1);
}


