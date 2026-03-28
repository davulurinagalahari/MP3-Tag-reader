#include <stdio.h>
#include <string.h>
#include "common.h"
int main(int argc, char *argv[])
{
    Mp3Info mp3info;
    if (argc < 2)
    {
        printf("Usage:\n");
        printf("For help menu: %s --help\n", argv[0]);
        printf("For viewing: %s -v <filename.mp3>\n", argv[0]);
        printf("For editing: %s -e <modifier> <new content> <file name>\n", argv[0]);
        return 1;
    }
    if (strcmp(argv[1], "-v") == 0)
    {
        if (read_and_validate_args(argv, &mp3info) == 0)
        {
            if (open_files(&mp3info) != 0)
            {
                printf("MP3 file not found\n");
                return 1;
            }

            if (check_version(&mp3info) != 0)
            {
                printf("Unsupported MP3 version\n");
                return 1;
            }

            if (view_tag(argv, &mp3info) == 0)
            {
                printf("DETAILS DISPLAYED SUCCESSFULLY\n");
            }
            else
            {
                printf("Error displaying MP3 tags\n");
                return 1;
            }
        }
        else
        {
            printf("Invalid input for view operation\n");
            return 1;
        }
    }
    else if (strcmp(argv[1], "-e") == 0)
    {
        if (read_and_validate_args_edit(argv, &mp3info) == 0)
        {
            printf("Edit operation successful\n");
        }
        else
        {
            printf("Invalid input for edit operation\n");
            return  1;
        }
    }
    else if (strcmp(argv[1], "--help") == 0)
    {
        printf("Help Menu:\n");
        printf("-v <file.mp3>        View MP3 tags\n");
        printf("-e <tag> <value> <file.mp3>   Edit MP3 tag\n");
    }
    else
    {
        printf("Unsupported operation\n");
        return 1;
    }
    return 0;
}
