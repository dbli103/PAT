
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

pthread_rwlock_t rwlock = PTHREAD_RWLOCK_INITIALIZER;

int num = 0;
void* fun_read(void* arg)
{
    int index = *(int *)arg;

    while(1)
    {
        pthread_rwlock_rdlock(&rwlock);
        printf("pthread %d ,read num %d\n", index, num);
        
        pthread_rwlock_unlock(&rwlock);
        sleep(random() % 3 +1);
    }
}

void* fun_write(void* arg)
{
    int index = *(int *)arg;

    while(1)
    {
        pthread_rwlock_wrlock(&rwlock);
        printf("pthread %d ,write num %d\n", index, num++);
        
        pthread_rwlock_unlock(&rwlock);
        sleep(random() % 3 +1);
    }
}
int main()
{
    int i = 0;
    pthread_t tid[8] = {0};
    srandom(getpid());
    for(int i = 0; i < 8; i++)
    {
        if(i < 5)
        {
            pthread_create(&tid[i], NULL, fun_read, (void*)&i);
        }
        else
        {
            pthread_create(&tid[i], NULL, fun_write, (void*)&i);
        }
    }

    for(int j = 0; j < 8; j++)
    {
        pthread_join(tid[j], NULL);
    }
    pthread_rwlock_destroy(&rwlock);
}