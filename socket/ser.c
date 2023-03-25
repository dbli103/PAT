#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
//#include <winsock.h>
//#include <windows.h>

#include <sys/socket.h>
#include<arpa/inet.h>

typedef struct sockaddr_in SOCK;
int main()
{
    //创建socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);

    //给socket绑定端口和ip bind
    SOCK addr = {0};
    addr.sin_family = AF_INET;
    //addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port = htons(8000);
    inet_pton(AF_INET, "192.168.70.129", &addr.sin_addr.s_addr);
    bind(fd, (struct sockaddr *)&addr, sizeof(addr));

    //监听 listen 将套接字由主动变成被动
    //创建一个连接队列  

    listen(fd, 128);

    
    //accept 提取连接 从已完成队列提取连接 提取一个新的已连接套接字，用这个和client通信
    SOCK addr_accetp = {0};
    socklen_t i = sizeof(SOCK);
    int cfd = accept(fd, (struct sockaddr *)&addr_accetp, &i);

    char ip[16] = "";
    inet_ntop(AF_INET, &addr_accetp.sin_addr.s_addr, ip ,16);
    printf("new client ip %s port %d \n", ip , ntohs(addr_accetp.sin_port));

    //读写
    char buf[1024] = {0};
    while(1)
    {
        memset(buf, 0, sizeof(buf));
        int len = read(STDIN_FILENO, buf, sizeof(buf));
        write(cfd, buf, len);
        len = read(cfd, buf, 1024); 
        printf("%s\n", buf);       

    }
    //关闭
    close(cfd);
    close(fd);

}