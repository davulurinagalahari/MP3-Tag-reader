#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "common.h"

Status read_and_validate_args_edit(char *argv[], Mp3Info *mp3info)
{
    if (strcmp(argv[1], "-e") == 0)
    {
        printf("Edit operation selected.\n");

        if (strstr(argv[4], ".mp3") != NULL)
        {
            printf("MP3 file detected\n");
            mp3info->mp3_fname = argv[4];
            mp3info->orginal = argv[4];
        }
        else
        {
            printf("Error: Invalid file. Please provide a .mp3 file.\n");
            return 1;
        }

        mp3info->fptr_mp3 = fopen(mp3info->mp3_fname, "rb");
        if (mp3info->fptr_mp3 == NULL)
        {
            printf("Error: Unable to open source MP3 file %s\n", mp3info->mp3_fname);
            return 1;
        }
        printf("Opened source MP3 file successfully.\n");

        mp3info->new_mp3 = "new.mp3";
        mp3info->new_ftr = fopen(mp3info->new_mp3, "wb");
        if (mp3info->new_ftr == NULL)
        {
            printf("new file is not present\n");
            return 1;
        }
        printf("new mp3 is created\n");

        if (strcmp(argv[2], "-t") == 0)
            return edit_tag("TIT2", argv, mp3info);
        else if (strcmp(argv[2], "-a") == 0)
            return edit_tag("TPE1", argv, mp3info);
        else if (strcmp(argv[2], "-A") == 0)
            return edit_tag("TALB", argv, mp3info);
        else if (strcmp(argv[2], "-y") == 0)
            return edit_tag("TYER", argv, mp3info);
        else if (strcmp(argv[2], "-m") == 0)
            return edit_tag("TCON", argv, mp3info);
        else if (strcmp(argv[2], "-c") == 0)
            return edit_tag("COMM", argv, mp3info);
        else
        {
            printf("Error: Unknown tag option '%s'\n", argv[2]);
            return 1;
        }
    }
    else
    {
        printf("Error: Unsupported operation.\n");
        return 1;
    }
}

unsigned int big_to_little_edit(unsigned char *b)
{
    return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
}

void int_to_big_endian(unsigned char b[4], unsigned int size)
{
    b[0] = (size >> 24) & 0xFF;
    b[1] = (size >> 16) & 0xFF;
    b[2] = (size >> 8) & 0xFF;
    b[3] = size & 0xFF;
}

Status edit_tag(char *tag, char *argv[], Mp3Info *mp3Info)
{
    rewind(mp3Info->fptr_mp3);
    rewind(mp3Info->new_ftr);

    char new_content[100];
    strcpy(new_content, argv[3]);
    unsigned int size_content = strlen(new_content) + 1;

    char header[10];
    fread(header, 1, 10, mp3Info->fptr_mp3);
    fwrite(header, 1, 10, mp3Info->new_ftr);

    char TAGS[5];
    unsigned char size[4], flag[2];
    int found = 0;

    while (1)
    {
        if (fread(TAGS, 1, 4, mp3Info->fptr_mp3) != 4)
            break;

        TAGS[4] = '\0';

        if (!isalpha(TAGS[0]))
            break;

        fread(size, 1, 4, mp3Info->fptr_mp3);
        fread(flag, 1, 2, mp3Info->fptr_mp3);

        unsigned int TAG_size = big_to_little_edit(size);

        char *data = malloc(TAG_size);
        fread(data, 1, TAG_size, mp3Info->fptr_mp3);

        if (strcmp(TAGS, tag) == 0)
        {
            found = 1;
            unsigned char size_bytes[4];
            int_to_big_endian(size_bytes, size_content);

            fwrite(TAGS, 1, 4, mp3Info->new_ftr);
            fwrite(size_bytes, 1, 4, mp3Info->new_ftr);
            fwrite(flag, 1, 2, mp3Info->new_ftr);
            fwrite(new_content, 1, size_content, mp3Info->new_ftr);
        }
        else
        {
            fwrite(TAGS, 1, 4, mp3Info->new_ftr);
            fwrite(size, 1, 4, mp3Info->new_ftr);
            fwrite(flag, 1, 2, mp3Info->new_ftr);
            fwrite(data, 1, TAG_size, mp3Info->new_ftr);
        }

        free(data);
    }

    int ch;
    while ((ch = fgetc(mp3Info->fptr_mp3)) != EOF)
        fputc(ch, mp3Info->new_ftr);

    fclose(mp3Info->fptr_mp3);
    fclose(mp3Info->new_ftr);

    remove(mp3Info->orginal);
    rename("new.mp3", mp3Info->orginal);

    if (found)
    {
        printf("Tag '%s' edited successfully.\n", tag);
        return 0;
    }
    else
    {
        printf("Tag '%s' not found in file.\n", tag);
        return 1;
    }
}

