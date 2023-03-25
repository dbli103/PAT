
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
typedef struct node
{
    
    struct node *next;
    int val;
}NODE_T;

pthread_cond_t condlock = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

//链表头节点
NODE_T list = {0};
int num = 0;

void* producer(void *arg)
{
    NODE_T *node = NULL;
    while(1)
    {
        node = (NODE_T*)malloc(sizeof(NODE_T));
        if(node == NULL)
        {
            perror("malloc");
        }
        memset(node , 0x0 , sizeof(NODE_T));
        node->val = random() % 100 + 1;
        node->next = NULL;
        pthread_mutex_lock(&mutex); 
        
        //尾插
        list.next = node;
        list.val++;
        printf("list val++ %d\n", list.val);

        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&condlock); 
        sleep(2);
    }
    return NULL;
}

void* customer(void *arg)
{
    while(1)
    {
        pthread_mutex_lock(&mutex); 
        if(list.next == NULL)
        {
            pthread_cond_wait(&condlock, &mutex);//自动解锁，满足条件后自动加锁
            printf("pthread2 wait\n");
        }
        printf("pthread2 ok\n");
        NODE_T *tmp = list.next;
        if(tmp->next == NULL)
        {
            free(tmp);
            list.val--;
            list.next = NULL;
        }
        else{
            list.next = list.next->next;
            free(tmp);
            list.val--;
        }


        printf("list val-- %d\n", list.val);
        pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

int main()
{
    int i = 0;
    pthread_t tid[2] = {0};
    srandom(getpid());


    pthread_create(&tid[0], NULL, producer, NULL);
        
      
        
    pthread_create(&tid[1], NULL, customer, NULL);
 

    for(int j = 0; j < 2; j++)
    {
        pthread_join(tid[j], NULL);
    }
    pthread_cond_destroy(&condlock);
    pthread_mutex_destroy(&mutex);
}