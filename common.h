#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

/* Use int for Status (0 = success, 1 = failure) */
typedef int Status;

/* MP3 information structure */
typedef struct mp3tag_info
{
    char *mp3_fname;     // MP3 filename
    FILE *fptr_mp3;      // File pointer to MP3 file

    char *new_mp3;       // New filename for edited MP3
    FILE *new_ftr;       // File pointer for edited output

    char *orginal;       // Original MP3 filename
} Mp3Info;

/* -------- VIEW FUNCTIONS -------- */
Status read_and_validate_args(char *argv[], Mp3Info *mp3info);
int print_help_menu(void);
Status open_files(Mp3Info *mp3info);
Status check_version(Mp3Info *mp3info);
unsigned int big_to_little(unsigned char *b);
Status view_tag(char *argv[], Mp3Info *mp3info);

/* -------- EDIT FUNCTIONS -------- */
Status read_and_validate_args_edit(char *argv[], Mp3Info *mp3info);
unsigned int big_to_little_edit(unsigned char *b);
void int_to_big_endian(unsigned char b[4], unsigned int size);
Status edit_tag(char *tag, char *argv[], Mp3Info *mp3Info);

#endif

