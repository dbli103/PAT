//信号量为0 表示占用   1表示可用（wait减一）
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>

typedef struct node
{
    
    struct node *next;
    int val;
}NODE_T;

 sem_t sem1 = 4;

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

        sem_wait(&sem);
        //尾插
        list.next = node;
        list.val++;
        printf("list val++ %d\n", list.val);


        sem_post(&sem);  // == sem_post
        sleep(2);
    }
    return NULL;
}

void* customer(void *arg)
{
    while(1)
    {

        if(list.next == NULL)
        {
            sem_wait(&sem);//自动解锁，满足条件后自动加锁 == sem_wait
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

    }
    return NULL;
}

int main()
{
    int i = 0;
    pthread_t tid[2] = {0};
    srandom(getpid());
    sem_init(&sem,0,1);

    pthread_create(&tid[0], NULL, producer, NULL);
        
      
        
    pthread_create(&tid[1], NULL, customer, NULL);
 

    for(int j = 0; j < 2; j++)
    {
        pthread_join(tid[j], NULL);
    }
    sem_destroy(&sem);
}