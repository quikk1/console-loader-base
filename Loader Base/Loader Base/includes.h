#pragma once

using namespace std;

#define _CRT_SECURE_NO_WARNINGS
#define SECURITY_WIN32

#include <winsock2.h>
#include <WinInet.h>
#include <stdlib.h>  
#include <gdiplus.h>
#include < Winternl.h>
#include <Iphlpapi.h>
#include <winnt.h>
#include <tlhelp32.h>
#include <time.h>
#include <vector>
#include <debugapi.h>
#include <shlwapi.h>
#include <iostream>
#include <conio.h>
#include <string>
#include <ws2tcpip.h>
#include <windows.h>
#include <CommCtrl.h>
#include <mmsystem.h>
#include <VersionHelpers.h>
#include <ShlObj.h>
#include <Psapi.h>
#include <gdiplus.h>
#include <utility>
#include <fstream>
#include <DbgHelp.h>


#pragma comment(lib,"Winmm.lib")
#pragma comment(lib,"Comctl32.lib")
#pragma comment (lib,"Gdiplus.lib")
#pragma comment (lib, "ws2_32.lib" )
#pragma comment( lib, "Msimg32" )
#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "wininet")
#pragma comment(lib, "Dbghelp.lib")
#pragma comment (lib, "urlmon.lib")
#pragma comment(lib, "ComCtl32.lib")
#pragma comment(lib, "shlwapi.lib")


#include "tool.h"
#include "termcolor.h"
