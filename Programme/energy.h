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
#include <math.h>               /* for doing math */
#include <time.h>               /* for working with time */
#include <string.h>             /* for working with strings */

/* Symbolic Constants */

#define TRUE  1                 /* boolean value for true */
#define FALSE 0                 /* boolean value for false */

#define DAY_AHEAD 14            /* the release time of the day ahead prices */
#define DAY_HOURS 24            /* the amount of hours in a day */
#define DAY_IN_SECONDS 86400    /* the amount of seconds in a day */

#define JAN 1                   /* the number of the months and the current year */
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

/* energy.c */
void setup(void);               /* input: none, output: none */
void do_calculations(void);     /* input: none, output: none */
void present(void);             /* input: none, output: none */

/* data.c */
Price_data get_data(char filepath[], Date target_date);
void set_date(Date *date, char date_string[]);
int date_equals(Date *date_a, Date *date_b);
int date_diffrence_in_days(Date *date_a, Date *date_b);

void print_date(Date date);
void print_energy_price(Energy_price energy_price);
void print_price_data(Price_data price_data);

#endif /* ENERGY_H */
