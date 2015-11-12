#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

/*
 * Implement putenv_r, a reentrant version of putenv.
 * Make sure that your implementation is async-signal safe as well as thread-safe.
 */

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int
putenv_r(char *str)
{
    int ret;
    sigset_t zero_mask, old_mask;

    sigemptyset(&zero_mask);
    if ((ret = pthread_sigmask(SIG_BLOCK, &zero_mask, &old_mask)) != 0) {
        return ret;
    }

    pthread_mutex_lock(&mutex);
    if ((ret = putenv(str)) != 0) {
        pthread_mutex_unlock(&mutex);
        return ret;
    }
    pthread_mutex_unlock(&mutex);

    ret = pthread_sigmask(SIG_SETMASK, &old_mask, NULL);
    return ret;
}

int
main()
{
    return 0;
}
