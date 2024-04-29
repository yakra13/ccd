/*
- [x] Read data from a file
- [x] Write data to a file
- [x] Modify data in a file
- [x] Close an open file
- [x] Print file information to the console
- [x] Create a new file
- [x] Append data to an existing file
- [x] Delete a file
- [x] Determine the size of a file (in a UNIX-based operating system)
- [x] Determine location within a file
- [x] Insert data into an existing file
- [x] Open an existing file
*/
#include "file_management.h"

#define BUFF_SIZE 256

int main(int argc, char** argv)
{
    printf("Write to file:\n");
    WriteDataToFile(DEFAULT_FILE_PATH, DEFAULT_FILE_CONTENT);

    ReadDataFromFile(DEFAULT_FILE_PATH);

    printf("Append data.\n");
    AppendDataToFile(DEFAULT_FILE_PATH, "\nAdditional line added.\n");

    printf("Print file data INVALID PATH without line numbers.\n");
    PrintFileData("invalid.txt", false);
    printf("Print file data INVALID PATH with line numbers.\n");
    PrintFileData("invalid.txt", true);

    printf("Print file data VALID PATH without line numbers.\n");
    PrintFileData(DEFAULT_FILE_PATH, false);
    printf("Print file data VALID PATH with line numbers.\n");
    PrintFileData(DEFAULT_FILE_PATH, true);

    printf("Insert some text 25 characters in. INVALID PATH\n");
    InsertDataIntoFile("invalid.txt", 25, "_THIS_IS_INSERTED_");
    PrintFileData("invalid.txt", true);

    printf("Insert some text -25 characters in.\n");
    InsertDataIntoFile(DEFAULT_FILE_PATH, -25, "_THIS_IS_INSERTED_");
    PrintFileData(DEFAULT_FILE_PATH, true);

    printf("Insert some text beyond length of file.\n");
    InsertDataIntoFile(DEFAULT_FILE_PATH, 1000, "_THIS_IS_INSERTED_");
    PrintFileData(DEFAULT_FILE_PATH, true);

    printf("Insert some text 25 characters in.\n");
    InsertDataIntoFile(DEFAULT_FILE_PATH, 25, "_THIS_IS_INSERTED_");
    PrintFileData(DEFAULT_FILE_PATH, true);

    printf("Modify the contents. a becomes -\n");
    ModifyDataInFile(DEFAULT_FILE_PATH, 'a', '-');

    PrintFileData(DEFAULT_FILE_PATH, false);

    printf("Print file information. INVALID PATH\n");
    PrintFileInformation("invalid.txt");

    printf("Print file information.\n");
    PrintFileInformation(DEFAULT_FILE_PATH);

    printf("Delete file INVALID PATH.\n");
    DeleteFile("invalid.txt");

    printf("Delete file.\n");
    DeleteFile(DEFAULT_FILE_PATH);
   
    exit(EXIT_SUCCESS);
}

// - [ ] Create a new file
// - [ ] Write data to a file
void WriteDataToFile(char* path, char* data)
{
    FILE* f;
    f = fopen(path, "w");

    if (f == NULL)
    {
        printf("Failed to create new file.\n");
        return;
    }

    if ((fprintf(f, data)) < 0)
    {
        printf("Failed to write to file: %s", path);
    }

    fclose(f);
}

// - [ ] Read data from a file
// - [ ] Open an existing file
// - [ ] Close an open file
void ReadDataFromFile(char* path)
{
    char* buffer;
    FILE* f;
    f = fopen(path, "r");

    if (f == NULL)
    {
        printf("Failed to open file for reading.\n");
        return;
    }

    size_t l = GetFileLength(f);
    buffer = malloc(l);

    if (buffer != NULL)
    {
        fread(buffer, 1, l, f);
        printf("File contents: %s\n", buffer);
        free(buffer);
    }
    else
    {
        printf("Failed to malloc!!!\n");
    }

    fclose(f);
}

// - [ ] Append data to an existing file
void AppendDataToFile(char* path, char* data)
{
    FILE* f;
    f = fopen(path, "a");

    if (f == NULL)
    {
        printf("Failed to open file for appending.\n");
        return;
    }

    if ((fprintf(f, data)) < 0)
    {
        printf("Failed to write to file: %s\n", path);
    }

    fclose(f);
}

// - [ ] Delete a file
void DeleteFile(char* path)
{
    if(remove(path) == 0)
    {
        printf("Deleted %s\n", path);
    }
    else
    {
        printf("Failed to delete %s\n", path);
    }
}

// - [ ] Determine the size of a file (in a UNIX-based operating system)
size_t GetFileLength(FILE* file)
{
    size_t file_length = 0;

    if (file == NULL)
    {
        printf("Supplied file in NULL.\n");
        return 0;
    }

    fseek(file, 0, SEEK_END);
    file_length = ftell(file);
    fseek(file, 0, SEEK_SET);

    return file_length;
}

// - [ ] Determine location within a file
void PrintFileData(char* path, bool line_numbers)
{
    char* line = (char*)calloc(BUFF_SIZE, sizeof(char));

    if (line == NULL)
    {
        printf("Failed to calloc!!\n");
        return;
    }

    int line_count = 0;
    FILE* f;
    f = fopen(path, "r");

    if (f == NULL)
    {
        printf("Failed to open file for printing.\n");
        free(line);
        return;    
    }

    while((fgets(line, BUFF_SIZE, f)))
    {
        if(line_numbers)
        {
            line_count++;
            printf("%3d %s", line_count, line);
        }
        else
        {
            printf("%s", line);
        }
    }

    printf("\n");

    free(line);
    fclose(f);
}

// - [ ] Insert data into an existing file
void InsertDataIntoFile(char* path, size_t offset, char* data)
{
    FILE* f;
    FILE* tmp;

    if ((f = fopen(path, "r")) == NULL)
    {
        printf("Failed to open file.\n");
        return;
    }

    if ((tmp = fopen(TEMP_FILE, "w")) == NULL)
    {
        printf("Failed to create temp file.\n");
        fclose(f);
        return;
    }

    if(GetFileLength(f) < offset)
    {
        printf("Provided offset is out of bounds.\n");
        fclose(f);
        fclose(tmp);
        DeleteFile(TEMP_FILE);
        return;
    }

    for (size_t i = 0; i < offset; i++)
    {
        fputc(fgetc(f), tmp);
    }

    size_t data_length = strlen(data);
    char* ptr = data;

    for (size_t i = 0; i < data_length; i++)
    {
        fputc((int)(*ptr), tmp);
        ptr++;
    }

    int c;
    while ((c = fgetc(f)) != EOF)
    {
        fputc(c, tmp);
    }

    fclose(f);
    fclose(tmp);
    DeleteFile(path);
    rename(TEMP_FILE, path);
}

// - [ ] Modify data in a file
void ModifyDataInFile(char* path, char search, char replace)
{
    FILE* f;

    f = fopen(path, "r+");

    if (f == NULL)
    {
        printf("Could not open file.\n");
        return;
    }

    int c;
    int w = 0;
    int r = 0;
    while ((c = fgetc(f)) != EOF)
    {
        r = ftell(f);
        fseek(f, w, SEEK_SET);
        if (c == search)
        {
            fputc(replace, f);
        }
        else
        {
            fputc(c, f);
        }
        w = ftell(f);
        fseek(f, r, SEEK_SET);
    }

    fclose(f);
}

// - [ ] Print file information to the console
void PrintFileInformation(char* path)
{
    struct stat file_info;

    if (stat(path, &file_info) == -1)
    {
        printf("Failed to get file info\n");
        return;
    }

    printf("\tFile: %s\n", path);
    printf("\tSize: %ld bytes\n", file_info.st_size);
    printf("\tOwner UID: %d\n", file_info.st_uid);
    printf("\tGroup GID: %d\n", file_info.st_gid);
    printf("\tLast access time: %s", ctime(&file_info.st_atime));
    printf("\tLast modification time: %s", ctime(&file_info.st_mtime));
    printf("\tLast status change time: %s", ctime(&file_info.st_ctime));
}