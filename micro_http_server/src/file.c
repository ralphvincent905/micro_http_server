#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"

// Load file into memory
char* load_file(const char *path, int *size_out) {
    FILE *fp = fopen(path, "rb");
    if (!fp) return NULL;

    fseek(fp, 0, SEEK_END);
    int size = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    char *buffer = malloc(size);
    if (!buffer) {
        fclose(fp);
        return NULL;
    }

    fread(buffer, 1, size, fp);
    fclose(fp);

    *size_out = size;
    return buffer;
}

// Basic MIME type detection
const char* get_mime_type(const char *path) {
    const char *ext = strrchr(path, '.');
    if (!ext) return "text/plain";

    if (strcmp(ext, ".html") == 0) return "text/html";
    if (strcmp(ext, ".htm")  == 0) return "text/html";
    if (strcmp(ext, ".css")  == 0) return "text/css";
    if (strcmp(ext, ".js")   == 0) return "application/javascript";
    if (strcmp(ext, ".png")  == 0) return "image/png";
    if (strcmp(ext, ".jpg")  == 0) return "image/jpeg";
    if (strcmp(ext, ".jpeg") == 0) return "image/jpeg";
    if (strcmp(ext, ".gif")  == 0) return "image/gif";
    if (strcmp(ext, ".svg")  == 0) return "image/svg+xml";
    if (strcmp(ext, ".txt")  == 0) return "text/plain";

    return "application/octet-stream";
}
