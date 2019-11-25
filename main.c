//
//  main.c
//  FinalProject
//
//  Created by afieqha mieza azemi on 21/11/2019.
//  Copyright © 2019 afieqha mieza azemi. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void createFile(const char* filename);
void deleteFile(const char* filename);
void copyFile(const char* source_file, const char* target_file);
void createHelp(void);
void deleteHelp(void);
void copyHelp(void);

int main(int argc, const char * argv[])
{
    if (strcmp(argv[1], "create" ) == 0)
        createFile(argv[2]);
    else if (strcmp(argv[1], "delete" ) == 0)
        deleteFile(argv[2]);
    else if (strcmp(argv[1], "copy" ) == 0)
        copyFile(argv[2], argv[3]);
    
    return 0;
}

void createFile(const char* filename)
{
    FILE *fp;
    fp = fopen(filename, "a+");
    printf("File created successfully.\n");
}

void deleteFile(const char* filename)
{
    int ret = remove(filename);
    
    if(ret == 0)
        printf("File deleted successfully.\n");
    else
        printf("Error: unable to delete the file");
}

void copyFile(const char* source_file, const char* target_file)
{
    char ch;
    FILE *source, *target;
    
    source = fopen(source_file, "r");
    
    if (source == NULL)
    {
        printf("Press any key to exit...\n");
        exit(EXIT_FAILURE);
    }
    
    target = fopen(target_file, "w");
    
    if (target == NULL)
    {
        fclose(source);
        printf("Press any key to exit...\n");
        exit(EXIT_FAILURE);
    }
    
    while ((ch = fgetc(source)) != EOF)
        fputc(ch, target);
    
    printf("File copied successfully.\n");
    
    fclose(source);
    fclose(target);
}

void createHelp()
{
    puts("create accepts the name of the file that you want to create");
}

void deleteHelp()
{
    puts("delete accepts the name of the file you want to delete");
}

void copyHelp()
{
    puts("copy accepts the name of the file you want to copy from and the name of file you are copying into");
}


