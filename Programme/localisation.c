/*
 ===============================================================================
 * File: localisation.c             Date completed: 16th of November, 2020
 ===============================================================================
 * Programmers: Anders G.           E-mail: ageert20@student.aau.dk
 *              Christoffer J.              cjanss20@student.aau.dk
 *              Dennis L.                   dbla19@student.aau.dk
 *              Jamie H.                    jhamme20@student.aau.dk
 *              Loke W.                     lwalst20@student.aau.dk
 *              Mads L.                     mlundf20@student.aau.dk
 *              Master P.                   mprase20@student.aau.dk
 ===============================================================================
 * Study Group: A303
 * Supervisor: Kamal Shahid         Class: P1, Computer Science - Fall Semester
 ===============================================================================
 * Description: This file manages our text strings in local languages.
 ===============================================================================
 */

#include "./H_files/localisation.h"

void prn_debug(char string[])
{
    printf("%s", string);
}

void print_string_from_id(enum languages language, char target_id[])
{
    char id[64];
    char english[256];
    char danish[256];
    char line[1024];
    char filepath[] = "./Programme/dataset/localisation.txt";
    FILE *stream = fopen(filepath, "r");
    if(stream != NULL)
    {
        while (fgets(line, 1024, stream))
        {
            sscanf(line, "%[^,],%[^,],%[^.].", id, english, danish);
            if (strcmp(target_id, id) == 0)
            {
                prn_debug(language == 0 ? english : danish);    /* TODO: call the console manager instead */
            }
        }
    } else { printf("Failed to open file \"%s\"\n\n", filepath); }
}