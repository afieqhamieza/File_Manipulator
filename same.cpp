//
//  main.cpp
//  final
//
//  Created by afieqha mieza azemi on 25/11/2019.
//  Copyright © 2019 afieqha mieza azemi. All rights reserved.
//

#include <iostream>
using namespace std;

void createFile(const char* filename);
void deleteFile(const char* filename);
void copyFile(const char* source_file, const char* target_file);
void createHelp();
void deleteHelp();
void copyHelp();

int main(int argc, const char * argv[])
{
    if (strcmp(argv[1], "create" ) == 0)
    {
        if (strcmp(argv[2], "help") == 0)
            createHelp();
        else
            createFile(argv[2]);
    }
    else if (strcmp(argv[1], "delete" ) == 0)
    {
        if (strcmp(argv[2], "help") == 0)
            deleteHelp();
        else
            deleteFile(argv[2]);
    }
    else if (strcmp(argv[1], "copy" ) == 0)
    {
        if (strcmp(argv[2], "help") == 0)
            copyHelp();
        else
            copyFile(argv[2], argv[3]);
    }
    
    return 0;
}

void createFile(const char* filename)
{
    FILE *fp;
    fp = fopen(filename, "a+");
    cout << "File created successfully." << endl;
}

void deleteFile(const char* filename)
{
    int ret = remove(filename);
    
    if(ret == 0)
        cout << "File deleted successfully." << endl;
    else
        cout << "Error: unable to delete the file" << endl;
}

void copyFile(const char* source_file, const char* target_file)
{
    char ch;
    FILE *source, *target;
    
    source = fopen(source_file, "r");
    
    if (source == NULL)
    {
        cout << "Press any key to exit..." << endl;
        exit(EXIT_FAILURE);
    }
    
    target = fopen(target_file, "w");
    
    if (target == NULL)
    {
        fclose(source);
        cout << "Press any key to exit..." << endl;
        exit(EXIT_FAILURE);
    }
    
    while ((ch = fgetc(source)) != EOF)
        fputc(ch, target);
    
    cout << "File copied successfully." << endl;
    
    fclose(source);
    fclose(target);
}

void createHelp()
{
    cout << "create accepts the name of the file that you want to create" << endl;
}

void deleteHelp()
{
    cout << "delete accepts the name of the file you want to delete" << endl;
}

void copyHelp()
{
    cout << "copy accepts the name of the file you want to copy from and the name of file you are copying into" << endl;
}


