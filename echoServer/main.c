#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 50000

void str_echo(int sockconn)
{
    char buff[256];
    size_t n;
    while( (n = read(sockconn, buff, 256)) > 0)
    {
        write(sockconn, buff, n);
    }
}
int main()
{
    int socklisten, sockconn;
    struct sockaddr_in servaddr;
    pid_t childpid;
    char buff[256];
    socklisten = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    bind(socklisten, (struct sockaddr*)&servaddr, sizeof(servaddr));
    listen(socklisten, 5);
    for( ; ; )
    {
        sockconn = accept(socklisten, NULL, NULL);
        if( (childpid = fork()) == 0)
        {
            close(socklisten);
            str_echo(sockconn);
            exit(0);
        }
        close(sockconn);
    }
    close(socklisten);
    return 0;
}
