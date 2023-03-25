#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>

void* fun1(void *arg)
{
    printf("thread 1 !\n");
}
void* fun2(void *arg)
{
    printf("thread 2 !\n");
    pthread_exit((void*)1);
}
int main()
{
    int ret = 0;
    void *pret = NULL;
    pthread_t thread1 = 0;
    ret = pthread_create(&thread1, NULL, fun1, NULL);
    //sleep(1);
    int err = pthread_join(thread1, &pret);
    printf("pthread_join %ld\n", (long)pret);

    pthread_t thread2 = 0;
    ret = pthread_create(&thread2, NULL, fun2, NULL);
    //sleep(1);


    err = pthread_join(thread2, &pret);
    printf("pthread_join %ld\n", (long)pret);

    return 0;
}