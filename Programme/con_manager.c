/*
 ===============================================================================
 * File: con_manager.c              Date completed: 16th of November, 2020
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
 * Description: This file manages the console output.
 ===============================================================================
 */

#include "./H_files/con_manager.h"

/* Prints a given string to the console. */
void print_string(const char* string, int needs_newline)
{
    if (needs_newline) {printf("%s\n", string);} else {printf("%s", string);}
}

/* Functions for graphs, if we choose to use them. */
