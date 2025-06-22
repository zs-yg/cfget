#ifndef PROGRESS_H
#define PROGRESS_H

typedef struct {
    int width;
    char filled_char;
    char empty_char;
    char *color_code;
} ProgressBarStyle;

void init_progress_bar(ProgressBarStyle *style);
void update_progress_bar(float percentage, ProgressBarStyle *style);

#endif
