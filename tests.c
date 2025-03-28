#include <stdio.h>

#include "elock.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    ELock lock;

    int err;
    elock_init(lock, 0, err);

    elock_signal(lock, err);
    elock_signal(lock, err);
    elock_signal(lock, err);
    elock_wait(lock, err);
    elock_signal(lock, err);
    elock_wait(lock, err);

    elock_destroy(lock, err);

    printf("Done\n");
    return 0;
}
