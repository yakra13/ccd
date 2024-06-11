#include <errno.h>
#include <poll.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static const int32_t TIME_OUT = 5;
static const char* file_1 = "file_1.txt";
static const char* file_2 = "file_2.txt";

int32_t main()
{
    // Array of pollfd with number of files to be polled.
    struct pollfd fds[2];
    int32_t poll_result;

    // Open the files in read only non-blocking for use in poll().
    int32_t fd_1 = open(file_1, O_RDONLY | O_NONBLOCK);
    int32_t fd_2 = open(file_2, O_RDONLY | O_NONBLOCK);

    // Fail out on open errors.
    if (fd_1 < 0 || fd_2 < 0)
    {
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
        exit(EXIT_FAILURE);
    }
    else if (poll_result == 0)
    {
        printf("No data received within %d seconds.\n", TIME_OUT);
    }
    else
    {
        char c;
        FILE* f;
        // Print the files with POLLIN events.
        for (int32_t i = 0; i < 2; i++)
        {
            if (!fds[i].revents & POLLIN)
                continue;

            printf("Printing %s.\n", i == 0 ? file_1 : file_2);

            // Get the file stream
            f = fdopen(fds[i].fd, "r");

            while((c = fgetc(f)) != EOF)
                putchar(c);

            putchar('\n');
        }
    }

    close(fd_1);
    close(fd_2);

    return EXIT_SUCCESS;
}