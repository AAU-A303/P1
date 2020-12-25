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
 * Description: This is a header file for the user communication file. This
 *              holds all of our prototypes, symbolic constants and included
 *              libraries.
 ===============================================================================
 */

#ifndef USER_COM_H
#define USER_COM_H

/* Libraries */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "data.h"
#include "present.h"
#include "localisation.h"
#include <ctype.h>

/* Symbolic Constants */

#define TRUE  1                 /* boolean value for true */
#define FALSE 0                 /* boolean value for false */

#define DAY_AHEAD 14            /* the release time of the day ahead prices */
#define DAY_HOURS 24

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

void setup_user_data(User_data*);	/* input: data, output: none */
void set_language(User_data*);		/* input: data, output: none */
void set_date(User_data*); 			/* input: data, output: none */
void set_time(int*, User_data*);	/* input: hour, data, output: none */
int days_in_month(int, int);    	/* input: month, year, output: num of days */
int is_leap_year(int);          	/* input: year, output: whether is leap year */

int want_data_for_tomorrow(User_data);  /* input: data, output: user response */
int has_new_inquiry(User_data);         /* input: data, output: user response */

#endif /* USER_COM_H */
