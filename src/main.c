#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define MAX_LINE_LENGTH 256
#define MAX_PATH 260
#define TEMP_DIR getenv("TEMP")

int find_package_url(const char *package_name, char *url) {
    FILE *fp = fopen("dl_url.txt", "r");
    if (!fp) return 0;

    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), fp)) {
        char *delim = strchr(line, ':');
        if (!delim) continue;

        *delim = '\0';
        if (strcmp(line, package_name) == 0) {
            strcpy(url, delim + 1);
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

void install_package(const char *package_name) {
    char url[MAX_LINE_LENGTH] = {0};
    if (!find_package_url(package_name, url)) {
        printf("Package '%s' not found\n", package_name);
        return;
    }

    char temp_path[MAX_PATH];
    snprintf(temp_path, sizeof(temp_path), "%s\\%s.zip", TEMP_DIR, package_name);

    printf("Downloading %s...\n", package_name);
    DownloadProgress progress = {0};
    if (!download_file(url, temp_path, &progress)) {
        printf("Download failed\n");
        return;
    }

    printf("Opening archive...\n");
    if (open_archive(temp_path) != 0) {
        printf("Failed to open archive\n");
        return;
    }

    printf("Package '%s' installed successfully\n", package_name);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: cfget install <package_name>\n");
        return 1;
    }

    if (strcmp(argv[1], "install") == 0 && argc == 3) {
        install_package(argv[2]);
    } else {
        printf("Invalid command\n");
        return 1;
    }

    return 0;
}
