#ifndef UTILS_H
#define UTILS_H

#include "downloader.h"

extern bool download_file(const char *url, const char *output_path, DownloadProgress *progress);
extern int open_archive(const char *archive_path);

#endif
