/*15.9 Demonstrate the ability to reverse engineer a binary and identify key facts about it
*/

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define KEY_LENGTH 8

const char VALID_CHARS[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
const char VALID_CHARS_EXTENDED[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789!@#$%^&*()-_=+[]{}|;:,.<>?";

bool isCharValid(const char c, bool extended_set)
{
    int32_t length = 0;
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

    for (int32_t i = 0; i < length - 1; i++)
    {
        if (c == set[i])
            return true;
    }

    return false;
}

bool sanitize(const char* input, int32_t length, bool extended_set)
{
    for (int32_t i = 0; i < length; i++)
    {
        if (isCharValid(input[i], extended_set) == false)
        {
            return false;
        }
    }
    
    return true;
}

uint32_t sum(void* collection, int32_t size)
{
    uint8_t* d = (uint8_t*)collection;

    uint32_t total = 0;
    for (uint32_t i = 0; i < size; i++)
    {
        total += d[i];
    }
    
    return total;
}

bool validatePass(uint32_t seed, char* password)
{
    int32_t set_length = strlen(VALID_CHARS_EXTENDED);

    srand(seed);

    for (int32_t i = 0; i < KEY_LENGTH; i++)
    {
        char c_check = VALID_CHARS_EXTENDED[rand() % set_length];
        fputc(c_check, stdout);
        if (password[i] != c_check)
            return false;
    }
    fputc('\n', stdout);
    
    // password[KEY_LENGTH] = '\0';
    return true;
}

int32_t main()
{
    char username[100] = {0};
    char password[100] = {0};

    fgets(username, sizeof(username), stdin);

    if (sanitize(username, strlen(username), false) == false)
        return 0;


    fgets(password, sizeof(password), stdin);

    if (sanitize(password, strlen(password), true) == false)
        return 0;

    if (validatePass(sum(&username, strlen(username)), password))
    {
        if (snprintf(username, sizeof(username), "Hello, %s", username) < 0)
            return 1;
    }
    else
        fprintf(stderr, "Invalid username/password combination.\n");

    // Zero out the password
    if (memset(password, 0, sizeof(password)) != 0)
    {
        fprintf(stderr, "Failed to zero out memory\n");
        return 1;
    }

    //format string vulns
    //pass input to printf(input) is bad
    //printf("%s", input) is good
    // Secure code: use snprintf to safely format the string
    //snprintf(username, sizeof(username), "Hello, %s", username);

    return 0;
}