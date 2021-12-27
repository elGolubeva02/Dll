#include "../DllдляПрикладного/Header.h"//подключил заголовок из другого проекта
BOOL WINAPI DllMain(HINSTANCE hlnstDll, DWORD dwReason, LPVOID IpReserved)
{
	BOOL bAllWentWell = TRUE;
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}
	if (bAllWentWell)
		return TRUE;
	else
		return FALSE;
}
LPWSTR Reading(LPWSTR path)
{
	DWORD d = 0;
	HINSTANCE FileHandle = CreateFile(PATH, GENERIC_READ, FILE_SHARE_WRITE | FILE_SHARE_READ, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	LPWSTR ReadString = calloc(100500, sizeof(WCHAR));
	ReadFile(FileHandle, ReadString, 100500 * sizeof(WCHAR), &d, NULL);
	CloseHandle(FileHandle);
	ReadString[d / 2] = '\n';
	ReadString[d / 2 + 1] = '\0';
	return ReadString;
}
DWORD LpwstrToDword(LPWSTR str)
{
	DWORD dw = 0;
	for (size_t i = 0; i < wcslen(str); i++)
	{
		dw += (str[i] - '0');
		dw *= 10;
	}
	return dw / 10;
}
DWORD CountUsers(LPWSTR str)
{
	DWORD count = 0;
	for (size_t i = 0; i < wcslen(str); i++)
	{
		if (str[i] == L'\n') count++;
	}
	return count;
}
__declspec(dllexport) U* CreateUserArray(LPWSTR path, LPDWORD n)
{
	LPWSTR str = Reading(path);
	DWORD count = CountUsers(str);
	U* users = calloc(count, sizeof(U));
	DWORD poz = 0, zap = 0, ind = 0;
	LPWSTR strvozr = calloc(3, sizeof(TCHAR));
	for (size_t i = 1; i < wcslen(str); i++)
	{
		if (str[i] == '\n')
		{
			strvozr = calloc(3, sizeof(TCHAR));
			zap++;
			poz = 0;
			ind = 0;
		}
		else
		{
			if (str[i] == ';')
			{
				poz++;
				ind = 0;
			}
			else
			{
				if (poz == 0)
					users[zap].f[ind] = str[i];
				if (poz == 1)
					users[zap].i[ind] = str[i];
				if (poz == 2)
					users[zap].o[ind] = str[i];
				if (poz == 3)
					users[zap].g[ind] = str[i];
				if (poz == 4)
				{
					if (str[i] == '\r')
					{
						strvozr[ind] = '\0';
						users[zap].vozr = LpwstrToDword(strvozr);
						free(strvozr);
					}
					else strvozr[ind] = str[i];
				}
				ind++;
			}
		}
	}
	*n = count;
	return users;
}
__declspec(dllexport) U1* Ubel(U* users, LPDWORD count)
{
	DWORD indUser = 0, con = 0, f = 0;
	for (DWORD i = 0; i < *count; i++) 
	{
		if (users[i].vozr%5==0)
		{
			con++;
		}
	}
	con++;
	U1* Ubel = calloc(con, sizeof(U1));
	Ubel[0].f[0] = (WCHAR)65279;
	indUser++;
	for (DWORD i = 0; i < *count; i++) 
	{
		if (users[i].vozr % 5 == 0)
		{
			for (DWORD j = 0; j < wcslen(users[i].o); j++)
			{
				Ubel[indUser].f[j] = users[i].f[j];
			}
			for (DWORD j = 0; j < wcslen(users[i].i); j++)
			{
				Ubel[indUser].i[j] = users[i].i[j];
			}
			for (DWORD j = 0; j < wcslen(users[i].o); j++)
			{
				Ubel[indUser].o[j] = users[i].o[j];
			}
			Ubel[indUser].vozr = users[i].vozr;
			indUser++;
		}
	}
	*count = con;
	return Ubel;
}
__declspec(dllexport) float Age(U* users, LPDWORD count)
{
	float avg = 0;
	for (DWORD i = 1; i < *count; i++)
	{
		avg += users[i].vozr;
	}
	avg = avg / (*count - 1);
	return avg;
}
__declspec(dllexport) LPWSTR Dlina(U* users, LPDWORD count)
{
	DWORD ind = 0, indUser = 0, f = 0;
	DWORD max = 0;
	for (DWORD i = 0; i < *count; i++)
	{
		size_t l1 = strlen(users[i].f);
		size_t l2 = strlen(users[i].i);
		size_t l3 = strlen(users[i].o);
		if (l1 + l2 + l3 > max)
		{
			max = l1 + l2 + l3;
			ind = i;
		}
	}
	char third[512];
	swprintf(third, sizeof(third), L"%s%s%s", users[ind].f, users[ind].i, users[ind].o);
	return third;
}
__declspec(dllexport) DWORD kolvo(U* users, LPDWORD count)
{
	DWORD ind = 0, indUser = 0, con = 0, f = 0;
	LPWSTR str = L"м";
	DWORD countF = wcslen(str);
	for (DWORD i = 0; i < *count; i++)
	{
		for (DWORD j = 0; j < countF; j++)
		{
			if (users[i].f[j] == str[j] && countF == wcslen(users[i].f))
				ind++;
			else ind--;
		}
		if (ind == countF)
		{
			con++;
		}
		ind = 0;
	}
	con++;
	*count = con;
	return con;
}