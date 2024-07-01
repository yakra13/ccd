#include <poll.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const int TIME_OUT = 5;
static const char* file_1 = "file_1.txt";
static const char* file_2 = "file_2.txt";

int main()
{
    // Array of pollfd with number of files to be polled.
    struct pollfd fds[2] = {0};
    int poll_result;
    int fd_1, fd_2 = 0;

    // Zero out pollfd
    memset(&fds[0], 0, sizeof(struct pollfd));
    memset(&fds[1], 0, sizeof(struct pollfd));

    // Open the files in read only non-blocking for use in poll().
    // Fail out on open errors.
    fd_1 = open(file_1, O_RDONLY | O_NONBLOCK);
    if (fd_1 < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    fd_2 = open(file_2, O_RDONLY | O_NONBLOCK);
    if (fd_2 < 0)
    {
        close(fd_1);
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Assign the file descriptors to the pollfd struct
    fds[0].fd = fd_1;
    fds[0].events = POLLIN;

    fds[1].fd = fd_2;
    fds[1].events = POLLIN;

    // Poll the descriptors and handle the result.
    poll_result = poll(fds, 2, TIME_OUT * 1000);

    if (poll_result == -1)
    {
        perror("poll");
        close(fd_1);
        close(fd_2);
        exit(EXIT_FAILURE);
    }
    else if (poll_result == 0)
    {
        printf("No data received within %d seconds.\n", TIME_OUT);
        close(fd_1);
        close(fd_2);
        exit(EXIT_FAILURE);
    }
    else
    {
        char c;
        FILE* f_stream;
        // Print the files with POLLIN events.
        for (int32_t i = 0; i < 2; i++)
        {
            if (!(fds[i].revents & POLLIN))
                continue;

            printf("Printing %s.\n", i == 0 ? file_1 : file_2);

            // Get the file stream
            f_stream = fdopen(fds[i].fd, "r");
            if (f_stream == NULL)
            {
                printf("Error opening file.\n");
                close(fd_1);
                close(fd_2);
                exit(EXIT_FAILURE);
            }

            while((c = fgetc(f_stream)) != EOF)
                putchar(c);

            putchar('\n');

            fclose(f_stream);
        }
    }

    return EXIT_SUCCESS;
}