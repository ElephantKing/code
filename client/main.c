#include <stdio.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>

void str_echo(FILE* fp, int sockfd)
{
    char buff_write[256], buff_read[256];
    while( (fgets(buff_write, 256, fp) != NULL) )
    {
        write(sockfd, buff_write, strlen(buff_write));
        if(read(sockfd, buff_read, 256) == 0)
            exit(0);
        fputs(buff_read, stdout);
    }
}
int main(int argc, char* argv[])
{
    int sockfd;//用于连接
    struct sockaddr_in servaddr;

    if(argc != 2)
    {
        exit(0);//err_quit("aaaa");
    }

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(50000);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    str_echo(stdin, sockfd);
    close(sockfd);

    return 0;
}
