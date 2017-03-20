/*
 *根据TCP/IP协议进行客户机与服务机的设计
 */
#include<stdlib.h>
#include<stdio.h>
#include<Winsock2.h>
#include<windows.h>
#pragma comment(lib , "ws2_32.lib")
/*
 *定义线程接收的结构体
 */
typedef struct
{
    SOCKET client ;
int id ;
} Client_Socket ;

/*
 *服务器线程
 */
 DWORD WINAPI  thread(LPVOID p) ;
 /*
 *为客户端开启的服务端线程
 */
DWORD WINAPI  thread_server(LPVOID p) ;
/*
 *服务端线程
 */
DWORD WINAPI  thread_client(LPVOID p) ;
/*
 *测试主函数
 */
int main()
{
    //初始化WinSock
    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
if(WSAStartup(wVersionRequested,&wsaData) != 0)
    {
        printf("初始化WinSock失败！\n") ;
return 0 ;
    }

   //开启服务端线程
    HANDLE handle = CreateThread(NULL , 0 , thread_server , NULL , 0 , NULL) ;

    //为服务端线程等待1秒
WaitForSingleObject(handle, 1000);

    //开启客户端线程

    HANDLE handle1 = CreateThread(NULL , 0 , thread_client , NULL , 0 , NULL) ;

     //一直等待客户端
WaitForSingleObject(handle1, INFINITE);

return 0 ;
}
/*
 *初始化服务端线程
 */
DWORD WINAPI  thread_server(LPVOID p)
{
int client_num = 0 ;
    SOCKET clientSocket[10] ; //初始化10个客户段SOCKET

    SOCKET sock ;
    struct sockaddr_in serv ;
    serv.sin_addr.s_addr = htonl(INADDR_ANY) ;
    serv.sin_family = AF_INET ;
    serv.sin_port = htons(5000) ; //设置端口为5000

int addrlen = sizeof(serv) ;

sock = socket(PF_INET , SOCK_STREAM , 0) ;
    if(bind(sock , (struct sockaddr*)&serv , addrlen)) //进行SOCKET与服务地址的绑定
    {
        printf("绑定失败！\n") ;
return 0 ;
    }
else
    {
        listen(sock , 5) ; //监听服务端SOCKET
while(true)
        {
printf("before accept !\n") ;
            clientSocket[client_num] = accept(sock  , (sockaddr*)&serv , &addrlen ) ; //循环等待直至客户端发送来连接请求
printf("accepted !\n") ;
if(clientSocket[client_num] == INVALID_SOCKET)
            {
printf("Error accept ! \n") ;
continue ;
            }
            Client_Socket cs ;
            cs.client = clientSocket[client_num] ;
            cs.id = client_num ;

            HANDLE handle = CreateThread(NULL , 0 , thread , &cs , 0 , NULL) ;

WaitForSingleObject(handle, INFINITE);

            client_num++ ;
printf("%d \n" , client_num) ;
        }
    }
}
/*
 *为客户端开启的线程
 */
 DWORD WINAPI  thread(LPVOID p)
 {
char buff[100] ;
      Client_Socket *clientSocket = (Client_Socket*)p ;
int result = 1 ;
while(result != SOCKET_ERROR)
      {
result = recv(clientSocket->client , buff , 100 , 0) ;
if(result != SOCKET_ERROR)
          {
printf("client %d : %s \n" , clientSocket->id , buff) ;
          }
      }
printf("Connect break ! \n") ;
 }
/*
 *客户端线程
 */
DWORD WINAPI  thread_client(LPVOID p)
{
char ip[35] = {"127.0.0.1"};
char buffer[100] ;
int ee = 1 ;
sockaddr_in cli ;
    cli.sin_addr.s_addr = inet_addr(ip) ;
    cli.sin_family = AF_INET ;
    cli.sin_port = htons(5000) ;
    SOCKET cliSocket ;
cliSocket = socket(AF_INET , SOCK_STREAM , 0) ;
while(connect(cliSocket , (sockaddr*)&cli , sizeof(cli))&&ee != 0)
    {
printf("Connect ....... \n") ;
    }
while(true)
    {
scanf("%s" , buffer) ;
send(cliSocket , buffer , 100 , 0) ;
    }
}
