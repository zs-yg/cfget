#include "net_utils.h"
#include <stdio.h>
#include <stdlib.h>

BOOL http_download(const char *url, const char *file_path, ProgressCallback callback) {
    HINTERNET hInternet = NULL;
    HINTERNET hConnect = NULL;
    HINTERNET hRequest = NULL;
    HANDLE hFile = INVALID_HANDLE_VALUE;
    BOOL result = FALSE;
    DWORD bytesRead = 0;
    DWORD totalSize = 0;
    DWORD downloadedSize = 0;
    BYTE buffer[4096];

    hInternet = InternetOpenA(USER_AGENT, INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    if (!hInternet) goto cleanup;

    hConnect = InternetOpenUrlA(hInternet, url, NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) goto cleanup;

    // 获取文件大小
    char szSize[32];
    DWORD dwSizeLen = sizeof(szSize);
    if (HttpQueryInfoA(hConnect, HTTP_QUERY_CONTENT_LENGTH, szSize, &dwSizeLen, NULL)) {
        totalSize = atol(szSize);
    }

    hFile = CreateFileA(file_path, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE) goto cleanup;

    while (InternetReadFile(hConnect, buffer, sizeof(buffer), &bytesRead) && bytesRead > 0) {
        DWORD bytesWritten;
        if (!WriteFile(hFile, buffer, bytesRead, &bytesWritten, NULL) || bytesWritten != bytesRead) {
            goto cleanup;
        }
        downloadedSize += bytesRead;
        if (callback && !callback(totalSize, downloadedSize)) {
            goto cleanup;
        }
    }

    result = TRUE;

cleanup:
    if (hFile != INVALID_HANDLE_VALUE) CloseHandle(hFile);
    if (hRequest) InternetCloseHandle(hRequest);
    if (hConnect) InternetCloseHandle(hConnect);
    if (hInternet) InternetCloseHandle(hInternet);
    return result;
}
