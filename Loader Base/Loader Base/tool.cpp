#include "includes.h"
#include "tool.h"
#include "termcolor.h"
#include <random>
using namespace std;

tool::tool()
{
}


tool::~tool()
{
}

void tool::set_console(int w, int h) {

	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);

	MoveWindow(console, r.left, r.top, w, h, TRUE);
}
void tool::checkInternet() {

	if (!InternetCheckConnectionA((LPCSTR)"http://www.google.com", FLAG_ICC_FORCE_CONNECTION, 0) && !InternetCheckConnectionA((LPCSTR)"http://www.facebook.com", FLAG_ICC_FORCE_CONNECTION, 0)) {

		int msgboxID = MessageBoxA(
			NULL,
			(LPCSTR)"There is a new version avaiable.",
			(LPCSTR)"Error",
			MB_OK
		);

		exit(-1);

	}
}

int tool::GetProcessIdByName(const std::string& p_name)
{
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 structprocsnapshot = { 0 };

	structprocsnapshot.dwSize = sizeof(PROCESSENTRY32);

	if (snapshot == INVALID_HANDLE_VALUE)return 0;
	if (Process32First(snapshot, &structprocsnapshot) == FALSE)return 0;

	while (Process32Next(snapshot, &structprocsnapshot))
	{
		if (!strcmp(structprocsnapshot.szExeFile, p_name.c_str()))
		{
			CloseHandle(snapshot);
			return structprocsnapshot.th32ProcessID;
		}
	}
	CloseHandle(snapshot);
	return 0;

}

string tool::httpRequest(string site, string param)
{
	HINTERNET hInternet = InternetOpenW(L"User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/51.0.2704.103 Safari/537.36", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0); 

	if (hInternet == NULL)
	{
		return "InternetOpenW failed(hInternet): " + GetLastError();
	}
	else
	{
		wstring widestr;
		for (int i = 0; i < site.length(); ++i)
		{
			widestr += wchar_t(site[i]);
		}
		const wchar_t* site_name = widestr.c_str();

		wstring widestr2;
		for (int i = 0; i < param.length(); ++i)
		{
			widestr2 += wchar_t(param[i]);
		}
		const wchar_t* site_param = widestr2.c_str();

		

		HINTERNET hConnect = InternetConnectW(hInternet, site_name, 80, NULL, NULL, INTERNET_SERVICE_HTTP, 0, NULL);

		if (hConnect == NULL)
		{
			return "InternetConnectW failed(hConnect == NULL): " + GetLastError();
		}
		else
		{
			const wchar_t* parrAcceptTypes[] = { L"text/*", NULL }; 

			HINTERNET hRequest = HttpOpenRequestW(hConnect, L"GET", site_param, NULL, NULL, parrAcceptTypes, 0, 0);

			if (hRequest == NULL)
			{
				return "HttpOpenRequestW failed(hRequest == NULL): " + GetLastError();
			}
			else
			{
				BOOL bRequestSent = HttpSendRequestW(hRequest, NULL, 0, NULL, 0);

				if (!bRequestSent)
				{
					return "!bRequestSent    HttpSendRequestW failed with error code " + GetLastError();
				}
				else
				{
					std::string strResponse;
					const int nBuffSize = 1024;
					char buff[nBuffSize];

					BOOL bKeepReading = true;
					DWORD dwBytesRead = -1;

					while (bKeepReading && dwBytesRead != 0)
					{
						bKeepReading = InternetReadFile(hRequest, buff, nBuffSize, &dwBytesRead);
						strResponse.append(buff, dwBytesRead);
					}
					return strResponse;
				}
				InternetCloseHandle(hRequest);
			}
			InternetCloseHandle(hConnect);
		}
		InternetCloseHandle(hInternet);
	}
}

bool tool::downloadFile(string url, string filepath) {

	DeleteUrlCacheEntry(url.c_str());

	HRESULT hr = URLDownloadToFile(
		NULL,  
		url.c_str(),
		filepath.c_str(),
		0,     
		NULL); 

	if (SUCCEEDED(hr))
		return true;
	else
		return false;

}


void tool::loadLibrary(string process, string dllpath) {

	DWORD dwProc = GetProcessIdByName(process);

	HANDLE hProc = OpenProcess(PROCESS_CREATE_THREAD | PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, dwProc);

	LPVOID allocMem = VirtualAllocEx(hProc, NULL, sizeof(dllpath), MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);

	WriteProcessMemory(hProc, allocMem, dllpath.c_str(), sizeof(dllpath), NULL);

	CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibrary, allocMem, 0, 0);

	CloseHandle(hProc);

}


void tool::checkPrivileges() {


	bool IsRunningAsAdmin = false;

	BOOL fRet = FALSE;
	HANDLE hToken = NULL;
	if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
		TOKEN_ELEVATION Elevation;
		DWORD cbSize = sizeof(TOKEN_ELEVATION);
		if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
			fRet = Elevation.TokenIsElevated;
		}
	}
	if (hToken) {
		CloseHandle(hToken);
	}
	IsRunningAsAdmin = fRet;

	if (!IsRunningAsAdmin) {

		int msgboxID = MessageBoxA(
			NULL,
			(LPCSTR)"Please, run as admin.",
			(LPCSTR)"Error",
			MB_OK
		);
		exit(-1);


	}

}

void tool::setupConsole(string consoletitle, int w, int h) {

	SetConsoleTitleA(consoletitle.c_str());
	set_console(w, h); 


}
void tool::title() {

	cout << termcolor::green << "//---LOADER BASE---\\" << endl << endl;

}

void tool::toggleText() {

	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
	DWORD mode = 0;

	GetConsoleMode(hStdin, &mode);
	SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT));

}

void tool::gotoxy(int x, int y) {

	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;

	SetConsoleCursorPosition(hCon, dwPos);


}

void tool::toggleCursor() {

	HANDLE hCon;
	hCon = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;

	SetConsoleCursorInfo(hCon, &cci);

}
