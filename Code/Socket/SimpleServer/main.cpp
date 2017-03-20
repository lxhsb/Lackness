#include <bits/stdc++.h>
#include <sys/socket.h>
#include <netinet/in.h>

using namespace std ;

int main()
{
    int server_fd ;
    sockaddr_in server ;
    server_fd = socket(AF_INET,SOCK_STREAM,0);
    if(server_fd == -1 )
    {
        cout<<" create server socket error "<<endl ;
        exit(1);
    }
    server.sin_port = htons(8000) ;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_family = AF_INET;

    int bind_status = bind(server_fd,(sockaddr*)(&server),sizeof(server));
    if(bind_status == -1 )
    {
        cout<<"bind failed "<<endl ;
        exit(1);
    }
    int listen_status = listen(server_fd,20);
    if(listen_status == -1 )
    {
        cout<<"listen failed"<<endl;
        exit(1);
    }
    //int client_fd ;
    sockaddr_in client;
    socklen_t length = sizeof(client);
    int client_fd = accept(server_fd,(sockaddr*)(&client),&length);
    if(client_fd<0)
    {
        cout<<"connect error "<<endl;
        exit(1);
    }
    char res[]= "accept";
    while(1+1>0)
    {
        char buff[2048];
        int len = recv(client_fd,buff,sizeof(buff),0);
        cout<<buff<<endl;
        send(client_fd,res,sizeof(res),0);
    }






}
