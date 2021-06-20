#include <windows.h>
#include <wininet.h>
#include <stdio.h>
#pragma comment(lib,"wininet")


int main(int argc, char* argv[])
{
HINTERNET hInternetSession;
HINTERNET hURL;
            // I'm only going to access 1K of info.
BOOL bResult;
DWORD dwBytesRead=1;

// Make internet connection.
hInternetSession = InternetOpen(
    TEXT("tesg"), // agent
    INTERNET_OPEN_TYPE_PRECONFIG,  // access
    NULL, NULL, 0);                // defaults

// Make connection to desired page.
hURL = InternetOpenUrl(
    hInternetSession,                       // session handle
    TEXT("http://vaido.world"),  // URL to access
    NULL, 0, 0, 0);                         // defaults

// Read page into memory buffer.

char buf[1024];

DWORD dwTemp;
HANDLE hFile = CreateFile(TEXT("пример.jpg"), GENERIC_WRITE, 0, NULL,
    CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

if (INVALID_HANDLE_VALUE == hFile) {
    return 0;
}

for (;dwBytesRead>0;)
{
    InternetReadFile(hURL, buf, (DWORD)sizeof(buf), &dwBytesRead);
    WriteFile(hFile, buf, dwBytesRead, &dwTemp, NULL);
}

// Close down connections.
InternetCloseHandle(hURL);
InternetCloseHandle(hInternetSession);

CloseHandle(hFile);


return 0;
}
