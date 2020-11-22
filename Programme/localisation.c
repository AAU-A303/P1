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

void print_string_from_id(enum languages language, char target_id[], int needs_newline){
    int language_index = 0;
    int language_indexes[language_count+1];
    char id[LINE_LENGTH];
    char languages[language_count][LINE_LENGTH];
    char line[LINE_LENGTH];

    int current_index = 0;
    int next_index = 0;
    int translation_length = 0;
    
    char filepath[] = "./Programme/dataset/localisation.txt";
    FILE *stream = fopen(filepath, "r");
    if(stream != NULL){
        while (fgets(line, LINE_LENGTH, stream)){
            get_localisation_indexes(language_indexes, line);
            sscanf(line, "%[^,],", id);
            if (strcmp(target_id, id) == 0){
                for(language_index = 0; language_index < language_count; language_index++){
                    current_index = language_indexes[language_index]+1;
                    next_index = language_indexes[language_index+1];
                    translation_length = (next_index - current_index);
                    strncpy(languages[language_index], &line[current_index], translation_length);
                    languages[language_index][translation_length] = '\0';
                }
                print_string(languages[language], needs_newline);
            }
        }
    } else { printf("Failed to open file \"%s\"\n\n", filepath); }
    fclose(stream);
}

void get_localisation_indexes(int indexes[], char localisation_string[]){
    int i = 0, j = 0;
    for(i = 0; i < LINE_LENGTH && j <= language_count; i++){
        if (localisation_string[i] == ','){
            indexes[j] = i;
            j++;
        }
    }
}