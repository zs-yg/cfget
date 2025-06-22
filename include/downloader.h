#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <stdbool.h>

typedef struct {
    long total_bytes;
    long downloaded_bytes;
    bool is_complete;
    bool is_error;
} DownloadProgress;

bool download_file(const char *url, const char *output_path, DownloadProgress *progress);
void display_progress(DownloadProgress *progress);

#endif
