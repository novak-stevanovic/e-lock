#include <stdio.h>

#include "e_lock.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    ELock lock;

    int err;
    e_lock_init(lock, 0, err);

    e_lock_signal(lock, err);
    e_lock_signal(lock, err);
    e_lock_signal(lock, err);
    e_lock_wait(lock, err);
    e_lock_signal(lock, err);
    e_lock_wait(lock, err);

    e_lock_destroy(lock, err);

    printf("Done\n");
    return 0;
}
