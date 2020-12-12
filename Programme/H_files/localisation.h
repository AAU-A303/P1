/*
 ===============================================================================
 * File: localisation.h             Date completed: 16th of November, 2020
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
 * Description: This is our main header file. This holds all of our prototypes,
 *              symbolic constants and included libraries.
 ===============================================================================
 */
#ifndef LOCALISATION_H
#define LOCALISATION_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define LINE_LENGTH 2048

#define LOCALISATION_FILE "./Programme/dataset/localisation.csv"

enum languages {
    english,
    danish,
    language_count
};

void print_string_from_id(enum languages, char[], int); /* input: language, target_id, needs_newline output: none */
void get_localisation_indexes(int[], char[]);           /* input: language, target_id output: none */
char* get_string_from_id(enum languages, char []);      /* input: indexes, localisation_string output: string */

#endif /* LOCALISATION_H */
