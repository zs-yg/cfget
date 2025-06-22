#include "progress.h"
#include <windows.h>
#include <stdio.h>

void init_progress_bar(ProgressBarStyle *style) {
    style->width = 50;
    style->filled_char = '=';
    style->empty_char = ' ';
    style->color_code = "\033[34m"; // 蓝色
}

void update_progress_bar(float percentage, ProgressBarStyle *style) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    WORD saved_attributes = consoleInfo.wAttributes;
    
    // 设置蓝色文本
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    
    int pos = (int)(percentage * style->width);
    printf("\r[");
    for (int i = 0; i < style->width; ++i) {
        if (i < pos) printf("%c", style->filled_char);
        else printf("%c", style->empty_char);
    }
    printf("] %.1f%%", percentage * 100);
    fflush(stdout);
    
    // 恢复原色
    SetConsoleTextAttribute(hConsole, saved_attributes);
}
