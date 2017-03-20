/*
 *����TCP/IPЭ����пͻ��������������
 */
#include<stdlib.h>
#include<stdio.h>
#include<Winsock2.h>
#include<windows.h>
#pragma comment(lib , "ws2_32.lib")
/*
 *�����߳̽��յĽṹ��
 */
typedef struct
{
    SOCKET client ;
int id ;
} Client_Socket ;

/*
 *�������߳�
 */
 DWORD WINAPI  thread(LPVOID p) ;
 /*
 *Ϊ�ͻ��˿����ķ�����߳�
 */
DWORD WINAPI  thread_server(LPVOID p) ;
/*
 *������߳�
 */
DWORD WINAPI  thread_client(LPVOID p) ;
/*
 *����������
 */
int main()
{
    //��ʼ��WinSock
    WORD wVersionRequested = MAKEWORD(2,2);
    WSADATA wsaData;
if(WSAStartup(wVersionRequested,&wsaData) != 0)
    {
        printf("��ʼ��WinSockʧ�ܣ�\n") ;
return 0 ;
    }

   //����������߳�
    HANDLE handle = CreateThread(NULL , 0 , thread_server , NULL , 0 , NULL) ;

    //Ϊ������̵߳ȴ�1��
WaitForSingleObject(handle, 1000);

    //�����ͻ����߳�

    HANDLE handle1 = CreateThread(NULL , 0 , thread_client , NULL , 0 , NULL) ;

     //һֱ�ȴ��ͻ���
WaitForSingleObject(handle1, INFINITE);

return 0 ;
}
/*
 *��ʼ��������߳�
 */
DWORD WINAPI  thread_server(LPVOID p)
{
int client_num = 0 ;
    SOCKET clientSocket[10] ; //��ʼ��10���ͻ���SOCKET

    SOCKET sock ;
    struct sockaddr_in serv ;
    serv.sin_addr.s_addr = htonl(INADDR_ANY) ;
    serv.sin_family = AF_INET ;
    serv.sin_port = htons(5000) ; //���ö˿�Ϊ5000

int addrlen = sizeof(serv) ;

sock = socket(PF_INET , SOCK_STREAM , 0) ;
    if(bind(sock , (struct sockaddr*)&serv , addrlen)) //����SOCKET������ַ�İ�
    {
        printf("��ʧ�ܣ�\n") ;
return 0 ;
    }
else
    {
        listen(sock , 5) ; //���������SOCKET
while(true)
        {
printf("before accept !\n") ;
            clientSocket[client_num] = accept(sock  , (sockaddr*)&serv , &addrlen ) ; //ѭ���ȴ�ֱ���ͻ��˷�������������
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
 *Ϊ�ͻ��˿������߳�
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
 *�ͻ����߳�
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
