#include <string.h>
#include <Winsock2.h>

#define DEST_IP "127.0.0.1"

#define DEST_PORT 1434

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

int sockfd,n;

struct sockaddr_in dest_addr;

sockfd = socket(AF_INET, SOCK_STREAM, 0);

dest_addr.sin_family = AF_INET;

dest_addr.sin_port = htons(DEST_PORT);

dest_addr.sin_addr.s_addr = inet_addr(DEST_IP);

//bzero(&(dest_addr.sin_zero));
n=connect(sockfd, (struct sockaddr *)&dest_addr, sizeof(struct sockaddr));
if(n==-1){
  printf("�˿�û�п���");
}else{
  printf("�˿ڿ���");
}
}
