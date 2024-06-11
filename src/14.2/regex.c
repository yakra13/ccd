#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int32_t main()
{
    // Capture group pattern
    const char* pattern = "(\\w+)@(\\w+)\\.(\\w+)";
    const char* sample = "example@test.com";
    char* output_buffer = (char*)calloc(256, sizeof(char));

    regex_t regex;
    regmatch_t matches[4];
    int32_t regex_result;

    // Compile the regular expression
    regex_result = regcomp(&regex, pattern, REG_EXTENDED);

    if (regex_result != REG_NOERROR)
    {
        regerror(regex_result, &regex, output_buffer, sizeof(output_buffer));
        printf("Could not compile regex: %s\n", output_buffer);
        exit(EXIT_FAILURE);
    }

    // Execute the regular expression
    regex_result = regexec(&regex, sample, 4, matches, 0);

    if (regex_result == REG_NOERROR) 
    {
        printf("Match found:\n");
        // Loop thru each match group and print the matches
        for (int i = 0; i < 4; i++)
        {
            if (matches[i].rm_so != -1)
            {
                // Get the length of the match string
                int32_t l = matches[i].rm_eo - matches[i].rm_so;
                // Copy the string to output buffer
                snprintf(output_buffer, l + 1, "%.*s", l, sample + matches[i].rm_so);
                printf("Group %d: %s\n", i, output_buffer);
            }
        }
    } 
    else if (regex_result == REG_NOMATCH)
    {
        printf("No match\n");
    }
    else
    {
        regerror(regex_result, &regex, output_buffer, sizeof(output_buffer));
        printf("Regex match failed: %s\n", output_buffer);
        exit(EXIT_FAILURE);
    }

    regfree(&regex);
    free(output_buffer);

    return EXIT_SUCCESS;
}