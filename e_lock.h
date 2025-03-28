#ifndef _E_LOCK_H_
#define _E_LOCK_H_

#include <stdbool.h>
#include <sys/eventfd.h>
#include <errno.h>

/* Async-safe simple synchronization mechanism that utilizes Linux's eventfd. */
typedef struct ELock
{
    eventfd_t _efd;
} ELock;

/* Initializes the lock. If 'init_val' is 0, the ELock struct starts locked.
 * Otherwise(greater than 0), it starts unlocked. */
#define e_lock_init(lock, init_val, out_err)                                   \
{                                                                              \
    size_t val = ((init_val) > 1) ? 1 : 0;                                     \
                                                                               \
    (lock)._efd = eventfd(val, 0);                                             \
                                                                               \
    (out_err) = ((lock)._efd == -1) ? errno : 0;                               \
}                                                                              \

/* A call to this macro results in one of the two scenarios:
 * 1. If the lock is available (previously signaled), the call will return
 *    immediately, consuming the signal and allowing execution to continue.
 * 2. If the lock is not available (no previous signals), the calling thread 
 *    will block until another thread signals it by calling e_lock_signal(). */
#define e_lock_wait(lock, out_err)                                             \
{                                                                              \
    uint64_t val;                                                              \
    ssize_t ret = read((lock)._efd, &val, sizeof(uint64_t));                   \
                                                                               \
    (out_err) = (ret == -1) ? errno : 0;                                       \
}                                                                              \

/* This will signal one of the waiting threads to wake up. If no threads are
 * waiting, the next call to 'e_lock_wait' will be non-blocking. */
#define e_lock_signal(lock, out_err)                                           \
{                                                                              \
    uint64_t val = 1;                                                          \
    ssize_t ret = write((lock)._efd, &val, sizeof(uint64_t));                  \
                                                                               \
    (out_err) = (ret == -1) ? errno : 0;                                       \
}                                                                              \

/* Destroys the lock. */
#define e_lock_destroy(lock, out_err)                                          \
{                                                                              \
    ssize_t ret = close((lock)._efd);                                          \
                                                                               \
    (out_err) = (ret == -1) ? errno : 0;                                       \
}                                                                              \

#endif // _E_LOCK_H_
