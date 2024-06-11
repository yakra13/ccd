#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <unistd.h>

static const int32_t TIME_OUT = 5;
static const char* file_1 = "file_1.txt";
static const char* file_2 = "file_2.txt";

int32_t main()
{
    fd_set read_fds;
    struct timeval time_value;
    int32_t select_result, end_fd;

    // Open the files in read only non-blocking for use in select().
    int32_t fd_1 = open(file_1, O_RDONLY | O_NONBLOCK);
    int32_t fd_2 = open(file_2, O_RDONLY | O_NONBLOCK);

    if (fd_1 < 0 || fd_2 < 0)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // Use built-in macros to set the file descriptors.
    FD_ZERO(&read_fds);
    FD_SET(fd_1, &read_fds);
    FD_SET(fd_2, &read_fds);

    // Used to determine the range for select().
    end_fd = (fd_1 > fd_2 ? fd_1 : fd_2) + 1;

    // Set the time out values for select().
    time_value.tv_sec = TIME_OUT;
    time_value.tv_usec = 0;

    // Perform the select
    select_result = select(end_fd, &read_fds, NULL, NULL, &time_value);

    if (select_result == -1)
    {
        perror("select");
        exit(EXIT_FAILURE);
    }
    else if (select_result == 0)
    {
        printf("No data received within %d seconds.\n", TIME_OUT);
    }
    else
    {
        char c;
        FILE* f;
        int32_t cur_fd = 0;
        // Print the files with where is set is true.
        for (int32_t i = 0; i < 2; i++)
        {
            cur_fd = i == 0 ? fd_1 : fd_2;

            if (!FD_ISSET(cur_fd, &read_fds))
                continue;

            printf("Printing %s.\n", i == 0 ? file_1 : file_2);

            // Get the file stream
            f = fdopen(cur_fd, "r");

            while((c = fgetc(f)) != EOF)
                putchar(c);

            putchar('\n');
        }
    }

    close(fd_1);
    close(fd_2);

    return EXIT_SUCCESS;
}