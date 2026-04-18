#ifndef HTTP_H
#define HTTP_H

// Handle a single client connection
void handle_client(int client_fd, const char *www_dir);

#endif
