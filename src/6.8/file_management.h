#pragma once
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

#define DEFAULT_FILE_PATH "test.txt"
#define TEMP_FILE "temp.tmp"
#define DEFAULT_FILE_CONTENT "Default text to write to file.\n"

void AppendDataToFile(char* path, char* data);
void DeleteFile(char* path);
size_t GetFileLength(FILE* file);
void InsertDataIntoFile(char* path, size_t offset, char* data);
void ModifyDataInFile(char* path, char search, char replace);
void PrintFileData(char* path, bool line_numbers);
void PrintFileInformation(char* path);
void ReadDataFromFile(char* path);
void WriteDataToFile(char* path, char* data);