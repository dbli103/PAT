
//pthread_mutex_lock();
//pthread_mutex_trylock();
//pthread_mutex_timedlock();
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//pthread_mutex_destroy(&mutex);


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void* fun1(void *arg)
{
    int i = 0;
    //pthread_mutex_t mutex = *(pthread_mutex_t*)arg;
    pthread_mutex_lock(&mutex);
    while(1)
    {
        printf("thread 1 %d\n", i++);
        if(i > 50)
            break;
    }
    pthread_mutex_unlock(&mutex);
}
void* fun2(void *arg)
{
    int i = 100;
    //pthread_mutex_t mutex = *(pthread_mutex_t*)arg;
    pthread_mutex_lock(&mutex);
    while(1)
    {
        printf("thread 1 %d\n", i++);
        if(i > 150)
            break;
    }
    pthread_mutex_unlock(&mutex);
}
int main()
{
    int ret = 0;
    void *pret = NULL;
    pthread_t thread1 = 0;

    //pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
    ret = pthread_create(&thread1, NULL, fun1, NULL);
    //sleep(1);


    pthread_t thread2 = 0;
    ret = pthread_create(&thread2, NULL, fun2,  NULL);
    //sleep(1);

    int err = pthread_join(thread1, &pret);
    printf("pthread_join %ld\n", (long)pret);
    err = pthread_join(thread2, &pret);
    printf("pthread_join %ld\n", (long)pret);

    pthread_mutex_destroy(&mutex);
    //pthread_mutex_destroy(&mutex2);
    return 0;
}