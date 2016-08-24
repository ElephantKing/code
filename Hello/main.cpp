#include <stdio.h>
#include <netinet/in.h>     //sockaddr_in
#include <string.h>             //bzero
#include <arpa/inet.h>      //htol,htos
#include <time.h>                 //time
#include <unistd.h>             //write
int main()
{
    int sockfd, socklisten;//连接套接字和监听套接字
    struct sockaddr_in servaddr;//主机地址族
    char buff[256];
    time_t ticks;
    socklisten = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port  = htons(60000);

    bind(socklisten, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(socklisten, 5);
    for( ; ; )
    {
        sockfd = accept(socklisten, NULL, NULL);
        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        printf("%s", buff);
        write(sockfd, buff, sizeof(buff));
        close(sockfd);
    }
}
