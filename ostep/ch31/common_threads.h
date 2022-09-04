#ifndef __common_threads_h__
#define __common_threads_h__

#include <pthread.h>
#include <assert.h>
#include <sched.h>

#ifdef __linux__
#include <semaphore.h>
#else
#include <dispatch/dispatch.h>
#endif

#define Pthread_create(thread, attr, start_routine, arg) assert(pthread_create(thread, attr, start_routine, arg) == 0);
#define Pthread_join(thread, value_ptr)                  assert(pthread_join(thread, value_ptr) == 0);

#define Pthread_mutex_lock(m)                            assert(pthread_mutex_lock(m) == 0);
#define Pthread_mutex_unlock(m)                          assert(pthread_mutex_unlock(m) == 0);
#define Pthread_cond_signal(cond)                        assert(pthread_cond_signal(cond) == 0);
#define Pthread_cond_wait(cond, mutex)                   assert(pthread_cond_wait(cond, mutex) == 0);

#define Mutex_init(m)                                    assert(pthread_mutex_init(m, NULL) == 0);
#define Mutex_lock(m)                                    assert(pthread_mutex_lock(m) == 0);
#define Mutex_unlock(m)                                  assert(pthread_mutex_unlock(m) == 0);
#define Cond_init(cond)                                  assert(pthread_cond_init(cond, NULL) == 0);
#define Cond_signal(cond)                                assert(pthread_cond_signal(cond) == 0);
#define Cond_wait(cond, mutex)                           assert(pthread_cond_wait(cond, mutex) == 0);

#ifdef __linux__
#define Sem_init(sem, value)                             assert(sem_init(sem, 0, value) == 0);
#define Sem_wait(sem)                                    assert(sem_wait(sem) == 0);
#define Sem_post(sem)                                    assert(sem_post(sem) == 0);
#else
struct rk_sema {
    dispatch_semaphore_t sem;
};
typedef struct rk_sema sem_t;

static inline void rk_sema_init(struct rk_sema *s, uint32_t value) {
    dispatch_semaphore_t *sem = &s->sem;
    *sem = dispatch_semaphore_create(value);
}
static inline void rk_sema_wait(struct rk_sema *s) {
    dispatch_semaphore_wait(s->sem, DISPATCH_TIME_FOREVER);
}
static inline void rk_sema_post(struct rk_sema *s) {
    dispatch_semaphore_signal(s->sem);
}
#define Sem_init(sem, value)  rk_sema_init(sem, value);
#define Sem_wait(sem)         rk_sema_wait(sem);
#define Sem_post(sem)         rk_sema_post(sem);
#endif

#endif // __common_threads_h__
