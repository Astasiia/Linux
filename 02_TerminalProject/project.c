#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int SIZE_BUFFER = 128;
const int SIZE_INFO = 10;
const int DELTA = 2;
const int SHIFT = strlen("0000: ");
const int ERROR_OPEN_FILE = 1;

int *updateSizeInfoBuffer(int *old_buffer, int *size) {
    int i;
    int *buffer = malloc((*size) * 2 * sizeof(int));
    for (i = 0; i < (*size); i++)
        buffer[i] = old_buffer[i];
    free(old_buffer); *size = (*size) * 2;
    return buffer;
}

char *updateSizeBuffer(char *old_buffer, int *size) {
    int i;
    char *buffer = malloc((*size) * 2 * sizeof(char));
    for (i = 0; i < (*size); i++)
        buffer[i] = old_buffer[i];
    free(old_buffer); *size = (*size) * 2;
    return buffer;
}

char *readFile(FILE *name) {
    char c; int i = 0, size = SIZE_BUFFER;
    char *buffer = malloc(size * sizeof(char));
    while ((c = fgetc(name)) != EOF) {
        if (i == size - 1) buffer = updateSizeBuffer(buffer, &size);
        buffer[i] = c; i++;
    }
    buffer[i + 1] = 0;
    return buffer;
}

char *processFile(char *name_file) {
    FILE *file = fopen(name_file, "r");
    if (!file)
        return NULL;
    char *textFile = readFile(file);
    fclose(file);
    return textFile;
}

int *stringFile(char *file) {
    int i = 0, k = 1, size = SIZE_INFO;
    int *infoBuffer = malloc(size * sizeof(int));
    infoBuffer[0] = 0;
    while (file[i] != 0) {
        if (k == size - 1) infoBuffer = updateSizeInfoBuffer(infoBuffer, &size);
        if (file[i] == '\n') {
            infoBuffer[k] = i + 1; k++;
        }
        i++;
    }
    infoBuffer[k] = -1;
    return infoBuffer;
}

int main (int argc, char **argv) {
    int width, height, start = 0, i, str, exitFlg = 0; char c;
    WINDOW *workWindow;
    char *file = processFile(argv[1]);
    char *nowString;
    int *string = stringFile(file);
    initscr();
    noecho();
    cbreak();
    printw("Name file: %s", argv[1]);
    refresh();

    width = COLS - 2 * DELTA;
    height = LINES - 2 * DELTA;
    workWindow = newwin(height, width, DELTA, DELTA);
    keypad(workWindow, TRUE);
    scrollok(workWindow, TRUE);

    while (1) {
        werase(workWindow);
        for (i = 0; i < height - 2 && string[i + start] != -1; i++) {
            if (string[i + start + 1] == -1)
                str = strlen(&file[string[i + start]]);
            else
                str = string[i + start + 1] - string[i + start];
            str = str < (width - SHIFT) ? str : (width - SHIFT);
            nowString = malloc((str + 1) * sizeof(char));
            nowString = strncpy(nowString, &file[string[i + start]], str);
            nowString[str] = 0;
            mvwprintw(workWindow, i + 1, 1, "%4d: %s", i + start, nowString);
            free(nowString);
        }
        box(workWindow, 0, 0);
        wrefresh(workWindow);
        switch (c = wgetch(workWindow)) {
            case ' ':
                if (string[start + i] != -1) start++;
                break;
            case 27:
            case 'q':
                exitFlg = 1; break;
            default:
                break;
        }
        if (exitFlg) {
            werase(workWindow);
            break;
        }
    }
    endwin();
    free(file); free(string);
    return 0;
}