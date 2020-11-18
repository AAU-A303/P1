/*
 ===============================================================================
 * File: user_com.h                 Date completed: 16th of November, 2020
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

#ifndef USER_COM_H
#define USER_COM_H

/* Libraries */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Symbolic Constants */

#define TRUE  1                 /* boolean value for true */
#define FALSE 0                 /* boolean value for false */

#define DAY_AHEAD 14            /* the release time of the day ahead prices */

#define JAN 1                   /* the number of the months and current year */
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
void get_user_input(void);      /* input: none, output: none */
void set_date(int*, int*, int); /* input: day, month, year, output: none */
void set_time(int*);            /* input: hour, output: none */
int days_in_month(int, int);    /* input: month, year, output: num of days */
int is_leap_year(int);          /* input: year, output: boolean */
int has_new_inquiry(void);      /* input: none, output: boolean */

#endif /* USER_COM_H */