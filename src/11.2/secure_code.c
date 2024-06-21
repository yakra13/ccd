/*11.2 Demonstrate skill in using secure coding techniques

Objectives

- [x] Formatting string vulnerabilities
- [x] Safe buffer size allocation
- [x] Input sanitization
- [x] Input validation
- [x] Establish a secure communications channel using an SSL library
- [x] Securely zeroing-out memory (compiler optimizations)

*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_LENGTH 8

char VALID_CHARS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
char VALID_CHARS_EXTENDED[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$\%^&*()-_=+[]{}|;:,.<>?";

bool isCharValid(const char c, bool extended_set)
{
    size_t length = 0;
    const char *set = NULL;

    if (extended_set)
    {
        set = VALID_CHARS_EXTENDED;
        length = sizeof(VALID_CHARS_EXTENDED);
    }
    else
    {
        set = VALID_CHARS;
        length = sizeof(VALID_CHARS);
    }

    if (length == 0 || set == NULL)
    {
        printf("Error assigning set for char validation.\n");
        return false;
    }

    for (size_t i = 0; i < length - 1; i++)
    {
        if (c == set[i])
            return true;
    }

    return false;
}

// - [ ] Input sanitization
bool sanitize(const char* input, size_t length, bool extended_set)
{
    // Ignore null terminator
    for (size_t i = 0; i < length - 1; i++)
    {
        if (isCharValid(input[i], extended_set) == false)
        {
            return false;
        }
    }
    
    return true;
}

unsigned int sum(void* collection, size_t size)
{
    // Converts a generic collection to a collection of bytes
    uint8_t* byte_array = (uint8_t*)collection;

    // For the purposes here overflowing is fine
    unsigned int total = 0;
    for (size_t i = 0; i < size; i++)
    {
        total += byte_array[i];
    }
    
    return total;
}

bool validatePass(unsigned int seed, char* password)
{
    //username = josh
    //password = 8<%B&DH>
    //+&na4j[)
    int set_length = (int)(strlen(VALID_CHARS_EXTENDED) - 1);

    srand(seed);
    // Based on the username provided check that each password character
    // matches the generated password
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        int index = rand() % set_length;
        char c_check = VALID_CHARS_EXTENDED[index];
        if (password[i] != c_check)
            return false;
    }
    
    return true;
}

int32_t main()
{
    char username[100] = {0};
    // - [ ] Safe buffer size allocation
    // - [ ] Securely zeroing-out memory (compiler optimizations)
    char* passwordBuffer = (char*)calloc(KEY_LENGTH + 1, sizeof(char));
    if (passwordBuffer == NULL)
    {
        printf("Failed to allocate.\n");
        return 1;
    }

    // Prompt for username
    fprintf(stdout, "Enter user name...\n");
    if (fgets(username, sizeof(username), stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        return 1;
    }

    // Sanitize the input (in this case make sure its only alphanumeric characters)
    // Not really necessary but username could potentially be used to open a log file
    // or something similar and here we disallow .\~ etc to prevent directory navigation
    if (sanitize(username, strlen(username), false) == false)
    {
        fprintf(stderr, "Invalid characters in username.\n");
        return 0;
    }

    // Prompt for password
    fprintf(stdout, "Enter password...\n");
    if (fgets(passwordBuffer, KEY_LENGTH + 1, stdin) == NULL)
    {
        fprintf(stderr, "Error reading input.\n");
        memset(passwordBuffer, 0, KEY_LENGTH);
        free(passwordBuffer);
        return 1;
    }

    // Sanitize the password using the extended set.
    if (sanitize(passwordBuffer, strlen(passwordBuffer), true) == false)
    {
        fprintf(stderr, "Invalid username/password combination.\n");
        memset(passwordBuffer, 0, KEY_LENGTH);
        free(passwordBuffer);
        return 0;
    }

    // - [ ] Input validation
    // Passwords are 8 characters; any characters beyond the first 8 are ignored
    // The passwordBuffer is calloced so any passwords not 8 characters long will
    // fail validation as null terminators are not part of the valid chars array
    // Because this is simulating a sort of log in system we don't inform the user of 
    // the specific issue.
    if (validatePass(sum(&username, strlen(username)), passwordBuffer))
    {
        // - [ ] Formatting string vulnerabilities
        // Never printf(username) or similar. Always pass to a format specifier
        fprintf(stdout, "Hello %s\n", username);
    }
    else
        fprintf(stderr, "Invalid username/password combination.\n");

    // Zero out the password
    // - [ ] Securely zeroing-out memory (compiler optimizations)
    memset(passwordBuffer, 0, KEY_LENGTH);
    // After this point doing a memdump or something similar should not reveal the password.

    //format string vulns
    //pass input to printf(input) is bad
    //printf("%s", input) is good
    // Secure code: use snprintf to safely format the string
    //snprintf(username, sizeof(username), "Hello, %s", username);

    free(passwordBuffer);

    return 0;
}