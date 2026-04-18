#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef _WIN32
    #include <winsock2.h>
    #include <ws2tcpip.h>
#else
    #include <arpa/inet.h>
    #include <sys/socket.h>
    #include <unistd.h>
#endif

#include "http.h"
#include "file.h"

#define REQ_BUF_SIZE 4096

static void send_all(int client, const char *data, int len) {
    int sent = 0;
    while (sent < len) {
        int n = send(client, data + sent, len - sent, 0);
        if (n <= 0) break;
        sent += n;
    }
}

static void send_response(int client, int status, const char *status_msg,
                          const char *mime, const char *body, int body_len) {
    char header[512];

    int header_len = snprintf(
        header, sizeof(header),
        "HTTP/1.1 %d %s\r\n"
        "Content-Type: %s\r\n"
        "Content-Length: %d\r\n"
        "Connection: close\r\n"
        "Server: MicroHTTP/1.0\r\n"
        "\r\n",
        status, status_msg, mime, body_len
    );

    send_all(client, header, header_len);

    if (body && body_len > 0)
        send_all(client, body, body_len);
}

void handle_client(int client_fd, const char *www_dir) {
    char buffer[REQ_BUF_SIZE];
    memset(buffer, 0, sizeof(buffer));

    int received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (received <= 0) {
        return;
    }

    char method[8], path[256], version[16];
    if (sscanf(buffer, "%7s %255s %15s", method, path, version) != 3) {
        send_response(client_fd, 400, "Bad Request", "text/plain",
                      "400 Bad Request", 15);
        return;
    }

    if (strcmp(method, "GET") != 0) {
        send_response(client_fd, 405, "Method Not Allowed", "text/plain",
                      "405 Method Not Allowed", 23);
        return;
    }

    if (strcmp(path, "/") == 0) {
        strcpy(path, "/index.html");
    }

    if (strstr(path, "..") != NULL) {
        send_response(client_fd, 403, "Forbidden", "text/plain",
                      "403 Forbidden", 13);
        return;
    }

    char fullpath[512];
    snprintf(fullpath, sizeof(fullpath), "%s%s", www_dir, path);

    int file_size = 0;
    char *file_data = load_file(fullpath, &file_size);

    if (!file_data) {
        send_response(client_fd, 404, "Not Found", "text/plain",
                      "404 Not Found", 13);
        return;
    }

    const char *mime = get_mime_type(fullpath);

    send_response(client_fd, 200, "OK", mime, file_data, file_size);

    free(file_data);
}
