/*
 ===============================================================================
 * File: data.h                     Date completed: 16th of November, 2020
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
#ifndef DATA_H
#define DATA_H

/* Libraries */

#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


/* Symbolic Constants */

#define TRUE  1                 /* boolean value for true */
#define FALSE 0                 /* boolean value for false */
#define DAY_HOURS 24            /* the amount of hours in a day */
#define DAY_IN_SECONDS 86400    /* the amount of seconds in a day */

/* data.c */

Price_data get_data(char filepath[], Date target_date);
void set_date(Date *date, char date_string[]);
int date_equals(Date *date_a, Date *date_b);
int date_diffrence_in_days(Date *date_a, Date *date_b);

#endif /* DATA_H */