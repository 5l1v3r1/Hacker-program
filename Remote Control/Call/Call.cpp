// Call.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

int main()
{
	BOOL bRet = false;
	//����һ��socket������
	SOCKET sockServer = INVALID_SOCKET;
	do
	{
		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		//�жϰ汾
		if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
		{
			break;

		}
		//��socket��Ϣ����������
		sockServer = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		//�ж��Ƿ�ɹ�
		if (INVALID_SOCKET == sockServer)
		{
			//ʧ���˾͹ر�
			break;
		}
		sockaddr_in addrServer = { 0 };

		addrServer.sin_family = AF_INET;
		//�����˿�
		addrServer.sin_port = htons(43156);
		//��
		if (SOCKET_ERROR == bind(sockServer, (SOCKADDR*)&addrServer, sizeof(addrServer)))
		{
			break;
		}
		//������û����������
		if (SOCKET_ERROR == listen(sockServer, SOMAXCONN))//�ڶ��������Ǽ����绰��
		{
			break;
		}
		//���ڿ��ż�������Ϊ�Ƿ�������Ҫ����û���нű�����������
		SOCKET sockClient = accept(sockServer, nullptr, nullptr);

		//�ж��Ƿ�������
		if (INVALID_SOCKET == sockClient)
		{
			//û�������Ӿ�����
			break;

		}
		char szComment[MAXBYTE] = { 0 };
		//��Ϊ�棬�ȴ���������
		//�������Ӻ�������
		while (true)
		{
			printf("\r\n�⼦�����ӿ��Կ��ƣ�");
			scanf("%s", szComment);
			send(sockClient, szComment, strlen(szComment), 0);
		}

		bRet = true;
	} while (false);
	WSACleanup();
	return 0;
}

