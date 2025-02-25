#include "philo.h"

// int k = 0;
// void *printhello(void *m1)
// {
//     pthread_mutex_t **m = (pthread_mutex_t **)m1;
//     pthread_mutex_t *m_l;
//     pthread_mutex_t *m_l1;
//     m_l = m[0];
//     m_l1 = m[1];

//     for (size_t i = 0; i < 1000000; i++)
//     {
//         pthread_mutex_lock(m_l1);
//         pthread_mutex_lock(m_l);
//             k++;
//         pthread_mutex_unlock(m_l);
//         pthread_mutex_unlock(m_l1);
//     }
//     return ((void*)101);
// }

// int main()
// {
//     pthread_t id1, id2;
//     pthread_mutex_t lock;
//     pthread_mutex_t lock2;
//     void *p[2];

//     pthread_mutex_init(&lock, NULL);
//     pthread_mutex_init(&lock2, NULL);
//     p[0] = &lock;
//     p[1] = &lock2;
//     pthread_create(&id1, NULL, printhello, p);
//     pthread_create(&id2, NULL, printhello, p);
//     pthread_join(id1, NULL);
//     pthread_join(id2, NULL);
//     printf("%d\n", k);
//     return 0;
// }

typedef struct mutxx
{
    pthread_mutex_t lock;
    pthread_mutex_t lock2;
}t_mutx;


void *printhell(void *v)
{
    pthread_mutex_lock(v);
    printf("hello\n");
    // pthread_mutex_unlock(v);
    return (void *)10;
}


int main()
{
    void *res = NULL;
    pthread_t id;
    t_mutx *locks;
    locks = malloc(sizeof(t_mutx));
    pthread_mutex_t lock;
    locks->lock = lock;

    
    pthread_mutex_init(&lock, NULL);
    pthread_create(&id, NULL, printhell, &lock);
    pthread_join(id, &res);
    pthread_create(&id, NULL, printhell, &lock);
    pthread_join(id, &res);
    printf("%ld\n", (long )res);
    pthread_mutex_destroy(&lock);
    return (0);
}