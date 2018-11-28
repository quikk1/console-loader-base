#pragma once
#include <Windows.h>
#include <string>
class tool
{
public:


	void set_console(int w, int h);
	void gotoxy(int x, int y);
	void toggleCursor();
	void setupConsole(std::string consoletitle, int w, int h);
	void title();
	void checkInternet();
	int GetProcessIdByName(const std::string& p_name);
	string httpRequest(string site, string param);
	void checkPrivileges(); 
	void toggleText();
	bool downloadFile(string url, string filepath);
	void loadLibrary(string process, string dllpath);

	tool();
	~tool();
};

