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

/* Prints string from a given id in a given language. */
void print_string_from_id(enum languages language, char target_id[], int needs_newline)
{
    char* result;

    result = get_string_from_id(language, target_id);

    if (needs_newline) {printf("%s\n", result);} else {printf("%s", result);};
}

/* Gets string from a given id in a given language. */
char* get_string_from_id(enum languages language, char target_id[])
{
    int language_indexes[language_count+1], start = 0, end = 0;
    char id[LINE_LENGTH], line[LINE_LENGTH], *result = {0};
    
    FILE *file = fopen(LOCALISATION_FILE, "r");
    if(file != NULL)
    {
        while (fgets(line, LINE_LENGTH, file)){
            sscanf(line, "%[^;];", id);
            if (strcmp(target_id, id) == 0)
            {
                get_localisation_indexes(language_indexes, line);
                start = language_indexes[language]+1;
                end = language_indexes[language+1];
                result = malloc(LINE_LENGTH * sizeof(char));
                strncpy(result, &line[start], end-start);
                result[end-start] = '\0';
            }
        }
    } else { printf("Failed to open file \"%s\"\n\n", LOCALISATION_FILE); }
    fclose(file);
    return result;
}

/* Gets the indexs of each localisation based on a given string */
void get_localisation_indexes(int indexes[], char localisation_string[]){
    int i = 0, j = 0;
    for(i = 0; i < LINE_LENGTH && j <= language_count; i++){
        if (localisation_string[i] == ';')
        {
            indexes[j] = i;
            j++;
        }
    }
}
