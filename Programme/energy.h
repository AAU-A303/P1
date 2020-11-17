/*
 ===============================================================================
 * File: energy.h                   Date completed: 16th of November, 2020
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

#ifndef ENERGY_H
#define ENERGY_H

/* Libraries */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>           /* for doing math */
#include <time.h>           /* for working with time */
#include <string.h>         /* for working with strings */

/* Symbolic Constants */

#define TRUE  1             /* boolean value for true */
#define FALSE 0             /* boolean value for false */

#define DAY_AHEAD 14        /* the release time of the day ahead prices */
#define DAY_HOURS 24        /* the amount of hours in a day */

#define JAN 1               /* the number of the months and the current year */
#define FEB 2
#define MAR 3
#define APR 4
#define MAY 5
#define JUN 6
#define JUL 7
#define AUG 8
#define SEP 9
#define OCT 10
#define NOV 11
#define DEC 12
#define CURRENT_YEAR 2020

/* Function Prototypes */

/* user_com.c */
void get_user_input(void);
void set_date(int*, int*, int);
void set_time(int*);
int days_in_month(int, int);
int is_leap_year(int);
int has_new_inquiry(void);

/* energy.c */
void setup(void);
void do_calculations(void);
void present(void);

#endif /* ENERGY_H */
