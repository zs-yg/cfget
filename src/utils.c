#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

int open_archive(const char *archive_path) {
    // 检查文件是否存在
    if (GetFileAttributesA(archive_path) == INVALID_FILE_ATTRIBUTES) {
        return -1;
    }

    // 使用ShellExecute打开文件
    HINSTANCE result = ShellExecuteA(
        NULL,               // hwnd
        "open",            // operation
        archive_path,      // file
        NULL,              // parameters
        NULL,              // directory
        SW_SHOWNORMAL      // show command
    );

    return (INT_PTR)result > 32 ? 0 : -1;
}
