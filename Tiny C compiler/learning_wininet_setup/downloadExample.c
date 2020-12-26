#include <windows.h>
#include <wininet.h>
#include <stdio.h>

#pragma comment (lib, "wininet")

int main(void)
{
    HINTERNET hInternet, hFile;
    char buf[1024];
    DWORD bytes_read;
    int finished = 0;
    hInternet = InternetOpen("", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (hInternet == NULL) {
        printf("InternetOpen failed\n");
        return 1;
    }
    hFile = InternetOpenUrl(hInternet, "http://www.martinbroadhurst.com", NULL, 0L, 0, 0);
    if (hFile == NULL) {
        printf("InternetOpenUrl failed\n");
        return 1;
    }
    while (!finished) {
        if (InternetReadFile(hFile, buf, sizeof(buf), &bytes_read)) {
            if (bytes_read > 0) {
                printf("%.*s", bytes_read, buf);
            }
            else {
                finished = 1;
            }
        }
        else {
            printf("InternetReadFile failed\n");
            finished = 1;
        }
    }
    InternetCloseHandle(hInternet);
    InternetCloseHandle(hFile);
             
    return 0;
}