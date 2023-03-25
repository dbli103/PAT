
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

pthread_cond_t condlock = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int num = 0;

void* fun1(void *arg)
{
    while(1)
    {
       pthread_mutex_lock(&mutex); 
       num = 1;
       pthread_mutex_unlock(&mutex);
       pthread_cond_signal(&condlock); 
       sleep(2);
    }
    return ;
}

void* fun2(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex); 
        if(num == 0)
        {
            pthread_cond_wait(&condlock, &mutex);//自动解锁，满足条件后自动加锁
        }
        printf("pthread2 ok\n");
        num = 0;

        pthread_mutex_unlock(&mutex);
    }
    return ;
}

int main()
{
    int i = 0;
    pthread_t tid[2] = {0};
    srandom(getpid());


    pthread_create(&tid[0], NULL, fun1, NULL);
        
      
        
    pthread_create(&tid[1], NULL, fun2, NULL);
 

    for(int j = 0; j < 2; j++)
    {
        pthread_join(tid[j], NULL);
    }
    pthread_cond_destroy(&condlock);
    pthread_mutex_destroy(&mutex);
}