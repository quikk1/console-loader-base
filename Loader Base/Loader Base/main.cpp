// SIMPLE LOADER BASE	
// -----------------------------------------------
// coded by https://github.com/quikk1 27/11/2018
// :license: GNU GPL, see LICENSE for details.
// -----------------------------------------------

#define VERSION (string)"1.0.0" //PROGRAM VERSION!
#define WEBSITE (string)"yourwebsite.com" //  !!! CHANGE THIS TO YOUR DOMAIN !!!

#include "includes.h"

tool* tools;

int main() {
	


	string username; 
	string password; 

#ifdef NDEBUG //If not debug release

	tools->checkPrivileges();	//Checks is program is running with admin privileges.
	tools->checkInternet();		//Checks if the user is connected to internet.
	

#endif // NDEBUG

	string check_version = tools->httpRequest(WEBSITE, "version.php"); //Gets version from website file using GET method.

	if (check_version == VERSION) { //Checks if version of program is equal to the latest.

		tools->setupConsole("Loader base", 400, 200); //Sets console title, width and heigth.

		tools->title(); // [[ cout << termcolor::green << "//---LOADER BASE---\\" << endl << endl; ]]

		tools->gotoxy(2, 3); cout << termcolor::magenta << "Username: " << termcolor::white;

		do {						//Asks for username while string username is empty.
			tools->gotoxy(12, 3);
			getline(cin, username);

		} while (username.empty());
		
		tools->gotoxy(2, 4); cout << termcolor::magenta << "Pass: ";

		tools->toggleText();	//Hides text.

		do {                      //Asks for password while string password is empty.

			tools->gotoxy(8, 4);
			getline(cin, password);

		} while (password.empty());

		tools->toggleText(); //Makes text visible again.

		HW_PROFILE_INFO hwProfileInfo;
		string hwid;

		if (GetCurrentHwProfile(&hwProfileInfo)) { //If we can read hwProfileInfo

			hwid = hwProfileInfo.szHwProfileGuid; //Gets hwid

			char request[512];
			sprintf(request, "/check.php?username=%s&password=%s&hwid=%s", username.c_str(), password.c_str(), hwid.c_str());

			string login_response = tools->httpRequest(WEBSITE, request); //Makes HTTP GET with login credential.

			string first_response = login_response.substr(0, 1); // Substracts first digit (LOGIN) from response
			string second_response = login_response.substr(1, 2); // Substracts second digit (HWID) from response

			if (first_response == "1") { //If password is correct

				if (second_response == "1" || second_response == "3") { //If hwid is correct or is not set yet (It will set it)

					system("cls"); //Clears screen
					tools->toggleCursor(); //Toggles cursor
					tools->title();

					tools->gotoxy(2, 2); cout << termcolor::magenta << "1. Inject 1.dll";
					tools->gotoxy(2, 3); cout << termcolor::magenta << "2. Inject 2.dll";
					int key_chosen = _getch(); //Gets key pressed

					switch (key_chosen) {

					case '1':						//If pressed 1
						system("cls");
						if (tools->downloadFile("yourwebsite.com/1.dll", "c://1.dll")) {	//If downloaded DLL from website [[ !!! CHANGE FIRST PARAM TO YOUR WEBSITE !!! ]]
							tools->loadLibrary("notepad.exe", "c://1.dll");					//Injects DLL to process
							cout << "1.dll injected into notepad.exe";
						}
						else {

							int msgboxID = MessageBoxA(
								NULL,
								(LPCSTR)"Couldn't download DLL.",
								(LPCSTR)"Loader base",
								MB_OK
							);
							exit(-1);

						}
						break;
					case '2':						//If pressed 2
						system("cls");
						if (tools->downloadFile("yourwebsite.com/2.dll", "c://2.dll")) {	//If downloaded DLL from website [[ !!! CHANGE FIRST PARAM TO YOUR WEBSITE !!! ]]
							tools->loadLibrary("notepad.exe", "c://2.dll");					//Injects DLL to process
							cout << "2.dll injected";
						}
						else {

							int msgboxID = MessageBoxA(
								NULL,
								(LPCSTR)"Couldn't download DLL.",
								(LPCSTR)"Loader base",
								MB_OK
							);
							exit(-1);

						}
						break;
					}


					Sleep(2000);
					exit(-1);

				}
				else {

					int msgboxID = MessageBoxA(
						NULL,
						(LPCSTR)"Wrong HWID.",
						(LPCSTR)"Loader base",
						MB_OK
					);
					exit(-1);

				}

			}
			else {

				int msgboxID = MessageBoxA(
					NULL,
					(LPCSTR)"Wrong password.",
					(LPCSTR)"Loader base",
					MB_OK
				);
				exit(-1);

			}

		}
		else {

			int msgboxID = MessageBoxA(
				NULL,
				(LPCSTR)"Couldn't read hwid.",
				(LPCSTR)"Loader base",
				MB_OK
			);
			exit(-1);

		}


	}
	else {

		int msgboxID = MessageBoxA(
			NULL,
			(LPCSTR)"There is a new version avaiable, please download it.",
			(LPCSTR)"Loader base",
			MB_OK
		);
		exit(-1);

	}
			
	return 0;
}