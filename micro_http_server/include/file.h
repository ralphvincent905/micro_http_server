#ifndef FILE_H
#define FILE_H

char* load_file(const char *path, int *size_out);

const char* get_mime_type(const char *path);

#endif
