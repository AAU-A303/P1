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
#include "localisation.h"

/* Symbolic Constants */

#define TRUE  1                 /* boolean value for true */
#define FALSE 0                 /* boolean value for false */
#define DAY_HOURS 24            /* the amount of hours in a day */
#define DAY_IN_SECONDS 86400    /* the amount of seconds in a day */
#define DATA_FILE "./Programme/dataset/dataset.txt"

/* Structs */

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    Date date;
    float prices[DAY_HOURS];            /* UNIT: DKK pr. MWh */
    float co2_emissions[DAY_HOURS];     /* UNIT: Grams pr. kWh */ 
} Energy_data;

typedef struct {
    Energy_data today;
    Energy_data tomorrow;
    int access_tomorrow;
    enum languages language;
} User_data;

/* Function Prototypes */

void get_data(User_data*, Date);            /* input: data, date output: none */
void date_set(Date*, char[]);               /* input: date, date_string output: none */
int date_equals(Date*, Date*);              /* input: date_a, date_b output: boolean */
int date_difference_in_days(Date*, Date*);  /* input: date_a, date_b output: boolean */
void reset_energy_data(Energy_data*);       /* input: energy_data output: none */

#endif /* DATA_H */
