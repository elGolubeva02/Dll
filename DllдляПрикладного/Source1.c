#include "header.h"
#include <strsafe.h>
#define PATHDLL L"DLL.dll"
#define PATHLIST L"Users.csv"
typedef U1* (_cdecl* MyFunction)(LPWSTR, LPDWORD);
typedef U* (_cdecl* MyFunction1)(U*, LPDWORD);
typedef float(_cdecl* MyFunction2) (U*, LPDWORD);
typedef LPWSTR(_cdecl* MyFunction3) (U*, LPDWORD);
typedef DWORD(_cdecl* MyFunction4) (U*, LPDWORD);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	//Задание 1
	HINSTANCE MyDLL;
	if (!(MyDLL = LoadLibrary(PATHDLL))) return 1;
	MyFunction UserList = (MyFunction)GetProcAddress(MyDLL, "CreateUserArray");
	MyFunction1 UserList1 = (MyFunction1)GetProcAddress(MyDLL, "Ubel");
	MyFunction2 AvgUserList = (MyFunction2)GetProcAddress(MyDLL, "Age");
	MyFunction3 MaxFIOUser = (MyFunction3)GetProcAddress(MyDLL, "Dlina");
	MyFunction4 KolvoM = (MyFunction4)GetProcAddress(MyDLL, "kolvo");
	DWORD count = 0;
	U* users = UserList(PATH, &count);
	DWORD w;
	HINSTANCE FileHandle = CreateFile(L"1.csv", GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	TCHAR otvFile[512];
	for (size_t i = 0; i < count-1; i++)
	{
		users[i].f[wcslen(users[i].f)] = (WCHAR)';';
		WriteFile(FileHandle, users[i].f, wcslen(users[i].f) * sizeof(WCHAR), &w, NULL);
		users[i].i[wcslen(users[i].i)] = (WCHAR)';';
		WriteFile(FileHandle, users[i].i, wcslen(users[i].i) * sizeof(WCHAR), &w, NULL);
		users[i].o[wcslen(users[i].o)] = (WCHAR)';';
		WriteFile(FileHandle, users[i].o, wcslen(users[i].o) * sizeof(WCHAR), &w, NULL);
		users[i].g[wcslen(users[i].g)] = (WCHAR)';';
		WriteFile(FileHandle, users[i].g, wcslen(users[i].g) * sizeof(WCHAR), &w, NULL);

		swprintf(otvFile, 512, TEXT("%d\r\n"), users[i].vozr);
		DWORD len = 0;
		while (otvFile[len] != '\0')
		{
			len++;
		}
		DWORD dz = 0;
		WriteFile(FileHandle,
			otvFile,
			len * (sizeof(char) * 2),
			&dz,
			NULL
		);
	}
	CloseHandle(FileHandle);
	//Задание 2
	DWORD w1;
	TCHAR otvFile2[512];
	DWORD count2 = count;
	U1* ubel = UserList1(users, &count2);
	HINSTANCE FileHandle2 = CreateFile(L"2.txt", GENERIC_WRITE, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	for (size_t i = 1; i < count2-1; i++)
	{
		ubel[i].f[wcslen(ubel[i].f)] = (WCHAR)' ';
		WriteFile(FileHandle2, ubel[i].f, wcslen(ubel[i].f) * sizeof(WCHAR), &w1, NULL);
		ubel[i].i[wcslen(ubel[i].i)] = (WCHAR)' ';
		WriteFile(FileHandle2, ubel[i].i, wcslen(ubel[i].i) * sizeof(WCHAR), &w1, NULL);
		ubel[i].o[wcslen(ubel[i].o)] = (WCHAR)' ';
		WriteFile(FileHandle2, ubel[i].o, wcslen(ubel[i].o) * sizeof(WCHAR), &w1, NULL);

		swprintf(otvFile2, 512, TEXT("%d\r\n"), ubel[i].vozr);
		DWORD len = 0;
		while (otvFile2[len] != '\0')
		{
			len++;
		}
		DWORD dz = 0;
		WriteFile(FileHandle2,
			otvFile2,
			len * (sizeof(char) * 2),
			&dz,
			NULL
		);
	}	
	CloseHandle(FileHandle2);
	//Задание 3 Средний возраст
	HKEY hKey = NULL;
	if (RegOpenKey(HKEY_CURRENT_USER, NULL, &hKey) != ERROR_SUCCESS)
		return 1;
	DWORD avg = AvgUserList(users, &count);
	/*avg = (avg + AvgUserList(users, &count)) / 2;*/
	if (RegSetValueEx(hKey, TEXT("ParamSize"), 0, REG_DWORD, (const BYTE*)&avg, sizeof(avg)) == ERROR_SUCCESS)
	{
		MessageBox(NULL, L"Ключ успешно создан", L"MyKey", MB_OK | MB_ICONINFORMATION);
	}
	DWORD DataType = 0;
	DWORD DataLen = 100500;
	DWORD SIZEE;
	TCHAR sZ[100];
	if (RegGetValueW(HKEY_CURRENT_USER, NULL, L"ParamSIze", RRF_RT_DWORD, &DataType, &SIZEE, &DataLen) == ERROR_SUCCESS)
	{
		StringCbPrintf(sZ, 100, TEXT("%d"), SIZEE);
		MessageBox(NULL, sZ, L"Средний возраст", MB_OK | MB_ICONINFORMATION);

	}
	else
	{
		MessageBox(NULL, L"Что-то пошло не так", L"Информация", MB_OK);
	}
	RegCloseKey(hKey);
	//Задание 3 Сама длинная ФИО
	HKEY hKey2 = NULL;
	if (RegOpenKey(HKEY_CURRENT_USER, NULL, &hKey2) != ERROR_SUCCESS) 
		return 1;
	if (RegSetValueW(hKey2, L"Mykey", REG_SZ, L"Значение по умолчанию", 22 * sizeof(WCHAR)) == ERROR_SUCCESS)
	{
		MessageBox(NULL, L"Ключ успешно создан", L"Информация", MB_OK);
	}
	LPWSTR maxst = MaxFIOUser(users, &count);
	TCHAR buff2[512];
	wsprintf(buff2, L"%s", maxst);
	if (RegSetValueExW(hKey2, L"Mykeys", NULL, REG_SZ, &buff2, 22 * sizeof(WCHAR)) == ERROR_SUCCESS)
	{
		MessageBox(NULL, &buff2, L"ФИО", MB_OK | MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(NULL, L"Что-то пошло не так", L"Информация", MB_OK);
	}
	RegCloseKey(hKey2);
	//Задание 3 Количество мужчин
	HKEY hKey3 = NULL;
	if (RegOpenKey(HKEY_CURRENT_USER, NULL, &hKey3) != ERROR_SUCCESS)
		return 1;
	DWORD kol = KolvoM(users, &count);
	if (RegSetValueEx(hKey3, TEXT("ParamSize3"), 0, REG_DWORD, (const BYTE*)&kol, sizeof(kol)) == ERROR_SUCCESS)
	{
		MessageBox(NULL, L"Ключ успешно создан", L"MyKey3", MB_OK | MB_ICONINFORMATION);
	}
	DWORD DataType2 = 0;
	DWORD DataLen2 = 100500;
	DWORD SIZEE2;
	TCHAR sZ2[100];
	if (RegGetValueW(HKEY_CURRENT_USER, NULL, L"ParamSIze3", RRF_RT_DWORD, &DataType2, &SIZEE2, &DataLen2) == ERROR_SUCCESS)
	{
		StringCbPrintf(sZ2, 100, TEXT("%d"), SIZEE2);
		MessageBox(NULL, sZ2, L"Количесво мужчин", MB_OK | MB_ICONINFORMATION);

	}
	else
	{
		MessageBox(NULL, L"Что-то пошло не так", L"Информация", MB_OK);
	}
	RegCloseKey(hKey3);
}