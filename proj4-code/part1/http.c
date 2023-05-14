#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include "http.h"

#define BUFSIZE 512

const char *get_mime_type(const char *file_extension) {
    if (strcmp(".txt", file_extension) == 0) {
        return "text/plain";
    } else if (strcmp(".html", file_extension) == 0) {
        return "text/html";
    } else if (strcmp(".jpg", file_extension) == 0) {
        return "image/jpeg";
    } else if (strcmp(".png", file_extension) == 0) {
        return "image/png";
    } else if (strcmp(".pdf", file_extension) == 0) {
        return "application/pdf";
    }

    return NULL;
}

int read_http_request(int fd, char *resource_name) {
    // TODO Not yet implemented
    
    if (read(fd, resource_name, BUFSIZE) < 0){
        perror("read in read_http error");
        return -1;
    }

    strtok(resource_name, " ");
    strtok(NULL, " "); //resource_name should now contain the file name
    
    return 0;
}

int write_http_response(int fd, const char *resource_path) {
    // TODO Not yet implemented
    int ch;
    struct stat st;
    ch = stat(resource_path, &st);
    
    char buf[BUFSIZE];
    if (ch == -1){
        // 404 not found
        sprintf(buf, "HTTP/1.0 404 Not Found\r\nContent-Length: 1\r\n\r\n");
        write(fd, &buf, strlen(buf) + 1);
        return 0;
    }

    // 200 OK
    sprintf(buf, "HTTP/1.0 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", get_mime_type(resource_path), (int) st.st_size);
    write(fd, &buf, strlen(buf) + 1);

    char content[BUFSIZE];
    int o = open(resource_path, O_CREAT|O_WRONLY|O_TRUNC, S_IRUSR|S_IWUSR);
    while (read(o, content, strlen(buf) + 1) > 0){
        write(fd, &content, strlen(buf) + 1);
    }

    return 0;
}
