int CUtil::GetOtherMacAddr(char *szIP,char *szBuf,int *pnBufLen)
{
    HRESULT hr;
    IPAddr  ipAddr;
    ULONG   pulMac[2];
    ULONG   ulLen;
    char strMacAddr[100]={0};
    ipAddr = inet_addr (szIP);
    memset (pulMac, 0xff, sizeof (pulMac));
    ulLen = 6;
    hr = SendARP (ipAddr, 0, pulMac, &ulLen);
    if(hr!=NO_ERROR)
        return 1;

    unsigned char * mac_addr=(unsigned char*)pulMac;
    //sprintf(strMacAddr,"%02X-%02X-%02X-%02X-%02X-%02X",mac_addr[0],mac_addr[1],
    //    mac_addr[2],mac_addr[3],mac_addr[4],mac_addr[5]);
    sprintf(strMacAddr,"%02X:%02X:%02X:%02X:%02X:%02X",mac_addr[0],mac_addr[1],
        mac_addr[2],mac_addr[3],mac_addr[4],mac_addr[5]);
    if ( *pnBufLen <= (int)strlen(strMacAddr) )
        return 2;
    strcpy(szBuf,strMacAddr);
    *pnBufLen = strlen(szBuf);

    return 0;
}

int CUtil::GetLocalMacAddr(char *szMac,int *pnMacLen,char *szIP /*=NULL */)
{
    //如果指定了IP，则直接按IP获取MAC
    //否则，需要先获取本机名称，再获取IP，再获取MAC
    if ( szIP != NULL )
        return GetOtherMacAddr(szIP,szMac,pnMacLen);

    char szHostName[256] = {0};
    int nRet = gethostname(szHostName,256);
    if ( nRet == SOCKET_ERROR )
        return 1;

    //获取本机名称
    struct hostent* hHost = gethostbyname(szHostName);
    if ( hHost == NULL ||  hHost->h_addr_list[0] == NULL )
        return 2;

    //获取IP地址
    memset(szHostName,0,256);
    strcpy(szHostName,inet_ntoa(*(struct in_addr *)hHost->h_addr_list[0]));

    //获取MAC
    return  GetOtherMacAddr(szHostName,szMac,pnMacLen);
}
