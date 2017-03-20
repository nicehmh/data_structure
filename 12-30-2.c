#include <winsock2.h>
#include <Iphlpapi.h>
#include <stdio.h>

void byte2Hex(unsigned char bData,unsigned char hex[])
{
    int high=bData/16,low =bData %16;
    hex[0] = (high <10)?('0'+high):('A'+high-10);
    hex[1] = (low <10)?('0'+low):('A'+low-10);
}

int getLocalMac(unsigned char *mac) //��ȡ����MAC��ַ
{
    ULONG ulSize=0;int i;
    PIP_ADAPTER_INFO pInfo=NULL;
    int temp=0;
    temp = GetAdaptersInfo(pInfo,&ulSize);//��һ�ε��ã���ȡ��������С
    pInfo=(PIP_ADAPTER_INFO)malloc(ulSize);
    temp = GetAdaptersInfo(pInfo,&ulSize);

    int iCount=0;
    while(pInfo)//����ÿһ������
    {
        //  pInfo->Address ��MAC��ַ
        for(i=0;i<(int)pInfo->AddressLength;i++)
        {
            byte2Hex(pInfo->Address[i],&mac[iCount]);
            iCount+=2;
            if(i<(int)pInfo->AddressLength-1)
            {
                mac[iCount++] = ':';
            }else
            {
                mac[iCount++] = '#';
            }
        }
        pInfo = pInfo->Next;
    }

    if(iCount >0)
    {
        mac[--iCount]='\0';
        return iCount;
    }
    else return -1;
}

int main(int argc, char* argv[])
{
    unsigned char address[1024];
    if(getLocalMac(address)>0)
    {
        printf("mac-%s\n",address);
    }else
    {
        printf("invoke getMAC error!\n");
    }
    return 0;
}



