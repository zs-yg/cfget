#include "downloader.h"
#include "net_utils.h"
#include "progress.h"
#include <stdio.h>

static ProgressBarStyle progress_style;
static BOOL progress_callback(DWORD total, DWORD downloaded) {
    float percentage = total > 0 ? (float)downloaded / total : 0;
    update_progress_bar(percentage, &progress_style);
    return TRUE; // 继续下载
}

bool download_file(const char *url, const char *output_path, DownloadProgress *progress) {
    init_progress_bar(&progress_style);
    progress_style.color_code = "\033[34m"; // 蓝色
    
    BOOL result = http_download(url, output_path, progress_callback);
    
    if (result) {
        printf("\nDownload completed successfully.\n");
        if (progress) {
            progress->is_complete = true;
            progress->is_error = false;
        }
    } else {
        printf("\nDownload failed.\n");
        if (progress) {
            progress->is_complete = false;
            progress->is_error = true;
        }
    }
    
    return result;
}

void display_progress(DownloadProgress *progress) {
    if (!progress) return;
    float percentage = progress->total_bytes > 0 ? 
        (float)progress->downloaded_bytes / progress->total_bytes : 0;
    update_progress_bar(percentage, &progress_style);
}
