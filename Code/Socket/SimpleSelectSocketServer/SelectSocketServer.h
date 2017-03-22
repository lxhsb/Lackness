//
// Created by wyy on 17-3-22.
//

#ifndef SIMPLESELECTSOCKETSERVER_SELECTSOCKETSERVER_H
#define SIMPLESELECTSOCKETSERVER_SELECTSOCKETSERVER_H

#include <sys/socket.h>
#include <sys/select.h>
#include <errno.h>
#include <cstring>
#include <netinet/in.h>
#include <ostream>
#include <arpa/inet.h>
#include <unistd.h>
class SelectSocketServer {

private:
    /*
     * use for client
     */
    int client_count ;//客户端个数
    int client_fd[FD_SETSIZE];//1024
    fd_set all_fd;//所有句柄的集合
    int max_fd ;//最大的句柄
    /*
     * use for server
     */
    sockaddr_in server_socket ;
    int server_socket_fd;
    timeval max_time ;//写死
    int port =8000;
    volatile bool have_to_stop= true;
    volatile bool is_running= false;//这点不是线程安全的  但是懒
    int init_server();
public :
    SelectSocketServer();
    int set_port(int _port);
    int start();
    void stop();
    int do_accept();
    int recv_and_send(fd_set *readfd);
};
#endif //SIMPLESELECTSOCKETSERVER_SELECTSOCKETSERVER_H
