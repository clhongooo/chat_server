#include <stdio.h>
#include <unistd.h>
#include <stddef.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <pthread.h>

#define CHAT_SOCKET "@iomn_chatsvr"
#define ROBOT_SOCKET "@iomn_robotsvr"

#define MSG_BUFF_LEN 10240

void * message_reader(void * param)
{
    int sockfd = *(int *)(param);
    int n;
    char read_buff[MSG_BUFF_LEN];

    while(1)
    {
        n = read(sockfd, read_buff, MSG_BUFF_LEN);
        if(n > 0)
        {
	        read_buff[n] = 0;
            printf("%s", read_buff);
        }
        else
        {
            break;
        }
    }

    int ret = 0;
    pthread_exit(&ret);
    return NULL;
}

void * message_writer(void * param)
{
    int sockfd = *(int *)param;
    char buffer[1024]{0};
    char * ptr;
    ssize_t writen;
    while((ptr = fgets(buffer, 1024, stdin)) != NULL) {

        // 过滤掉空行
        if(buffer[0] == '\n') continue;

        writen = write(sockfd, buffer, strlen(ptr));
        if(writen <= 0) 
        {
            printf("Write Data Failed, Exit\n");
            break;
        }
    }

    int ret = 0;
    pthread_exit(&ret);
    return NULL;
}

void print_usage()
{
    printf("Usage: diag_menu svrname\n");
    printf("Available svrname: robot\n");
}

const char * select_socket_name(const char * param)
{
    if(strcmp(param, "chat") == 0)
    {
        return CHAT_SOCKET;
    }

    if(strcmp(param, "robot") == 0)
    {
        return ROBOT_SOCKET;
    }

    return NULL;
}

int main(int argc, char * argv[])
{
    if(argc != 2)
    {
        print_usage();
        return 0;
    }

    const char * socket_name = select_socket_name(argv[1]);
    if(socket_name == NULL)
    {
        print_usage();
        return 0;
    }

    int connect_fd, ret;
    static struct sockaddr_un srv_addr;
    //creat unix socket
    connect_fd = socket(PF_UNIX, SOCK_STREAM, 0);
    if(connect_fd < 0)
    {
        perror("cannot create communication socket");
        return 1;
    }

    srv_addr.sun_family = AF_UNIX;
    strcpy(srv_addr.sun_path, socket_name);
    srv_addr.sun_path[0] = 0;
    socklen_t srv_len = strlen(socket_name) + offsetof(struct sockaddr_un, sun_path);

    ret = connect(connect_fd, (struct sockaddr*)&srv_addr, srv_len);
    if(ret==-1)
    {
        perror("Could not find the target server");
        close(connect_fd);
        return 1;
    }

    // Create one thread to read data from connct_fd
    pthread_t thread_read;
    pthread_create(&thread_read, NULL, message_reader, &connect_fd);

    pthread_t thread_write;
    pthread_create(&thread_write, NULL, message_writer, &connect_fd);

    void * thread_ret;
    pthread_join(thread_read, &thread_ret);

    pthread_cancel(thread_write);

    return 0;
}
