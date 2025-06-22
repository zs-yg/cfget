#ifndef NET_UTILS_H
#define NET_UTILS_H

#include <windows.h>
#include <wininet.h>

#define USER_AGENT "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.127 Safari/537.36"

typedef BOOL (*ProgressCallback)(DWORD total, DWORD downloaded);

BOOL http_download(const char *url, const char *file_path, ProgressCallback callback);

#endif
