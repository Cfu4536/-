#include "shlobj.h"
#include "string"
using namespace std;

int main() {
	//��ȡ����·��
	LPITEMIDLIST pidl;
	LPMALLOC pShellMalloc;
	char szDir[200];
	string desktop;
	if (SUCCEEDED(SHGetMalloc(&pShellMalloc))) {
		if (SUCCEEDED(SHGetSpecialFolderLocation(NULL, CSIDL_DESKTOP, &pidl))) {
			// ����ɹ�����true
			SHGetPathFromIDListA(pidl, szDir);
			pShellMalloc->Free(pidl);
		}
		pShellMalloc->Release();
	}
	desktop = string(szDir);
	strcat(szDir, "\\*");

	//�����ļ���
	WIN32_FIND_DATAA fileInfo;
	HANDLE hFile = FindFirstFileA(szDir, &fileInfo);

	if (hFile == INVALID_HANDLE_VALUE) {
		return -1;
	}

	do {
		//������ļ���
		if (fileInfo.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			char oldname[200];
			char newname[200];
			string pt = ".{20D04FE0-3AEA-1069-A2D8-08002B30309D}";
			//�Ƿ��Ѿ��޸�
			if (string(fileInfo.cFileName).find(pt) != string::npos ) {
				printf("no need!\n");
				continue;
			}
			strcpy(oldname, (desktop + "\\" + fileInfo.cFileName).c_str());
			strcpy(newname, (desktop + "\\" + fileInfo.cFileName + pt).c_str());
			printf("%s\n", newname);
			//������
			if (rename(oldname, newname) == 0)
				printf("�޸ĳɹ�\n");
			else
				perror("rename");
		}
	} while (FindNextFileA(hFile, &fileInfo));
	return 0;
}
