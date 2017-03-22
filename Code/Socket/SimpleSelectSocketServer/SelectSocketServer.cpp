//
// Created by wyy on 17-3-22.
//


#include "SelectSocketServer.h"

SelectSocketServer::SelectSocketServer()
{
    client_count = 0 ;
    memset(client_fd,-1,sizeof client_fd);
    server_socket_fd = -1 ;
}
int SelectSocketServer:: init_server() {//java 写习惯了  好喜欢用this...

    this->server_socket_fd = socket(AF_INET,SOCK_STREAM,0);//tcp ;
    if(server_socket_fd == -1 )
    {
        printf("create socket error %d %s\n",errno,strerror(errno));
        return -1 ;
    }
    /*
     * 端口快速释放
     */
    int reuse = 1;
    if (setsockopt(this->server_socket_fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)) == -1) {
        printf("port error \n");
        return -1;
    }
    memset(&this->server_socket,0,sizeof this->server_socket);
    server_socket.sin_port = htons(this->port);
    server_socket.sin_family = AF_INET;
    server_socket.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(server_socket_fd,(struct sockaddr*)&server_socket,sizeof(server_socket)) == -1) {
        //perror("bind error: ");
        printf("bind  error %d %s\n",errno,strerror(errno));
        return -1;
    }

    if (listen(server_socket_fd,1024) == -1) {
        //perror("bind error: ");
        printf("listen error %d %s\n",errno,strerror(errno));
        return -1;
    }
    return  1 ;//success


}

int SelectSocketServer::do_accept() {
    struct sockaddr_in cliaddr;
    socklen_t cliaddrlen;
    cliaddrlen = sizeof(cliaddr);
    int clifd = -1;

    printf("accpet clint proc is called.\n");

    ACCEPT:
    clifd = accept(server_socket_fd,(struct sockaddr*)&cliaddr,&cliaddrlen);

    if (clifd == -1) {
        if (errno == EINTR) {
            goto ACCEPT;
        } else {
            printf( "accept fail,error:%s\n", strerror(errno));
            return -1;
        }
    }

    printf( "accept a new client: %s:%d\n",
            inet_ntoa(cliaddr.sin_addr),cliaddr.sin_port);

    //将新的连接描述符添加到数组中
    int i = 0;
    for (i = 0; i < 1024; i++) {
        if (client_fd[i] < 0)
        {
            client_fd[i] = clifd;
            client_count++;
            break;
        }
    }

    if (i == FD_SETSIZE) {
        printf("too many clients.\n");
        return -1;
    }

}

int SelectSocketServer::recv_and_send(fd_set *readfd) {
    int i = 0, n = 0;
    int clifd;
    char buf[2048] = {0};
    for (i = 0;i <= client_count;i++) {
        clifd = client_fd[i];
        if (clifd < 0) {
            continue;
        }
        /*判断客户端套接字是否有数据*/
        if (FD_ISSET(clifd, readfd)) {
            //接收客户端发送的信息
            n = read(clifd, buf, 2048);
            if (n <= 0) {
                /*n==0表示读取完成，客户都关闭套接字*/
                FD_CLR(clifd, &all_fd);
                close(clifd);
                client_fd[i] = -1;
                continue;
            }
            //handle_client_msg(clifd, buf);
            printf("recv buf is :%s\n", buf);
            write(clifd, "ok receive!", strlen("ok receive!") +1);
        }
    }

}
int SelectSocketServer::set_port(int _port) {
    if(this->is_running == true)
        return -1 ;
    this->port = _port;
    return 1 ;

}
int SelectSocketServer::start() {
    is_running = true;
    if(init_server()<0)
    {
        return  -1 ;
    }
    printf("init finish\n");
    int  clifd = -1;
    int  retval = 0;
    fd_set *readfds =&all_fd;
    int i = 0;
    while (have_to_stop == false) {
        /*每次调用select前都要重新设置文件描述符和时间，因为事件发生后，文件描述符和时间都被内核修改啦*/
        FD_ZERO(readfds);
        /*添加监听套接字*/
        FD_SET(server_socket_fd, readfds);
        max_fd = server_socket_fd;

        /*添加客户端套接字*/
        for (i = 0; i < client_count; i++) {
           // clifd = s_srv_ctx->clifds[i];
            clifd = client_fd[i];
            /*去除无效的客户端句柄*/
            if (clifd != -1) {
                FD_SET(clifd, readfds);
            }
            max_fd = (clifd > max_fd ? clifd : max_fd);
        }
        /*开始轮询接收处理服务端和客户端套接字*/
        //timeval out = {30,0};
        this->max_time = {30,0};
        retval = select(max_fd + 1, readfds, NULL, NULL, &this->max_time);
        if (retval == -1) {
            printf( "select error:%s.\n", strerror(errno));
            return -1 ;
        }
        if (retval == 0) {
            printf( "select is timeout.\n");
            continue;
        }
        if (FD_ISSET(server_socket_fd, readfds)) {
            /*监听客户端请求*/
           // accept_client_proc(srvfd);
            do_accept();
        } else {
            /*接受处理客户端消息*/
            recv_and_send(readfds);
        }
    }
}
void SelectSocketServer::stop() {
    this->have_to_stop = true;
}