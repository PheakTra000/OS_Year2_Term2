#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[1024];

    // 1. Open the source file for reading only
    source_fd = open("result.txt", O_RDONLY);
    if (source_fd == -1) {
        perror("Error opening source file");
        exit(1);
    }

    // 2. Open/Create the destination file
    // O_WRONLY: Write only
    // O_CREAT: Create if it doesn't exist
    // O_TRUNC: Truncate to zero length if it exists
    // 0644: Permissions (read/write for owner, read for others)
    dest_fd = open("copyresult.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (dest_fd == -1) {
        perror("Error opening/creating destination file");
        close(source_fd);
        exit(1);
    }

    // 3. Read from source and write to destination using a buffer
    while ((bytes_read = read(source_fd, buffer, sizeof(buffer))) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("Error writing to destination file");
            break;
        }
    }

    // 4. Close the file descriptors
    close(source_fd);
    close(dest_fd);

    return 0;
}