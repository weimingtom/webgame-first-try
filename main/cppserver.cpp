//
//预计的SOKCET的服务器端
//使用SOCKET与客户端的flash socket交互，可以有更好的性能和实时性
//

#include <winsock2.h>

#include <stdio.h>
#include <stdlib.h>

#define DEFAULT_PORT   5150
#define DEFAULT_BUFFER 4096

#pragma comment(lib,"Ws2_32.lib")

int iPort = DEFAULT_PORT;
BOOL bInterface = FALSE,bRecvOnly = FALSE;

char szAddress[128];

static char* szPolicy = "<?xml version=\"1.0\"?><cross-domain-policy><allow-access-from domain=\"*\" to-ports=\"*\"/></cross-domain-policy>\0";

void useage()
{
	printf("userage: server [-p:x] [-i:IP] [-o]\n\n");
	printf("         -p:x    Port number to listen on\n");
	printf("         -i:str  interface to listen on\n");
	printf("         -o      Dont echo the data back\n\n");
	ExitProcess(1);
}

void ValidateArgs(int argc,char** argv)
{
	int i;

	for(i=1;i<argc;i++)
	{
		if((argv[i][0] == '-') || (argv[i][0] == '/'))
		{
			switch(tolower(argv[i][1]))
			{
				case 'p':
					iPort = atoi(&argv[i][3]);
				    break;
				case 'i':
					bInterface = TRUE;
				    if(strlen(argv[i]) > 3)
						strcpy(szAddress,&argv[i][3]);
					break;
				case 'o':
					bRecvOnly = TRUE;
					break;
				default:
					useage();
					break;
			}
		}
	}
}

DWORD WINAPI ClientThread(LPVOID lpParam)
{
	SOCKET sock=(SOCKET)lpParam;
	char szBuff[DEFAULT_BUFFER];
	int ret,nLeft,idx;
	char* sendbuff;
	BOOL IsClose = FALSE;

	while(1)
	{
		ret = recv(sock,szBuff,DEFAULT_BUFFER,0);
		if(ret == 0)
			break;
		else if(ret == SOCKET_ERROR)
		{
			printf("recv() failed: %d\n",WSAGetLastError());
			break;
		}
		szBuff[ret]='\0';
		printf("RECV-1:'%s'\n",szBuff);

		if(szBuff[0] == 'q' && szBuff[1] == 'u' && szBuff[2] == 'i' && szBuff[3] == 't')
			IsClose = TRUE;
		else
			sendbuff = szBuff;

		if(!bRecvOnly)
		{
			if(IsClose)
			{
				printf("close socket");
				ret = send(sock,"88",sizeof("88\n")+1,0);
				closesocket(sock);
				return 0;
			}
			nLeft = strlen(sendbuff);
			idx = 0;
			while(nLeft > 0)
			{
				ret = send(sock,&sendbuff[idx],nLeft,0);
				if(ret == 0)
					break;
				else
				{
					printf("send() failed:%d\n",WSAGetLastError());
					break;
				}
				nLeft -=ret;
				idx += ret;
			}
		}
	}
	return 0;
}

int main(int argc,char **argv)
{
	WSADATA wsd;
	SOCKET sListen,sClient;
	int iAddrSize;
	HANDLE hThread;
	DWORD dwThreadId;
	struct sockaddr_in local,client;

	ValidateArgs(argc,argv);
	if(WSAStartup(MAKEWORD(2,2),&wsd)!=0)
	{
		printf("Failed to load Winsock!\n");
		return 1;
	}

	sListen = socket(AF_INET,SOCK_STREAM,IPPROTO_IP);
	if(sListen == SOCKET_ERROR)
	{
		printf("socket() failed:%d\n",WSAGetLastError());
		return 1;
	}
	if(bInterface)
	{
		local.sin_addr.s_addr = inet_addr(szAddress);
		if(local.sin_addr.s_addr==INADDR_NONE)
			useage();
	}
	else
		local.sin_addr.s_addr = htonl(INADDR_ANY);
	local.sin_family = AF_INET;
	local.sin_port = htons(iPort);

	if(bind(sListen,(struct sockaddr*)&local,sizeof(local)) == SOCKET_ERROR)
	{
		printf("bind() failed: %d\n",WSAGetLastError());
		return 1;
	};
	listen(sListen,8);
	while(1)
	{
		iAddrSize = sizeof(client);
		sClient = accept(sListen,(struct sockaddr*)&client,&iAddrSize);
		if(sClient == INVALID_SOCKET)
		{
			printf("accept() failed: %d\n",WSAGetLastError());
			break;
		}
		printf("Accepted client:%s:%d\n",
			inet_ntoa(client.sin_addr),ntohs(client.sin_port));
		hThread = CreateThread(NULL,0,ClientThread,(LPVOID)sClient,0,&dwThreadId);
		if(hThread == NULL)
		{
			printf("CreateThread() failed: %d\n",GetLastError());
			break;
		}
		CloseHandle(hThread);
	}
	printf("close sock\n\n");
	closesocket(sListen);
	WSACleanup();
	return 0;
}