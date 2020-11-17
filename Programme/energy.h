/*
 * File: energy.h               Date completed: 16th of November, 2020
 * Programmers: Anders Geert    E-mail: ageert20@student.aau.dk
 *              Christoffer Jønsson     cjanss20@student.aau.dk
 *              Dennis Larsen           dbla19@student.aau.dk
 *              Jamie Hammer            jhamme20@student.aau.dk
 *              Loke Walsted            lwalst20@student.aau.dk
 *              Mads Lundfold           mlundf20@student.aau.dk
 *              Master Piyaboot         mprase20@student.aau.dk
 * Study Group: A303
 * Supervisor: Kamal Shahid     Class: P1, Computer Science - Fall Semester
 *
 * Description: This is our main header file. This holds all of our prototypes,
 *              symbolic constants and included libraries.
 */

#ifndef ENERGY_H
#define ENERGY_H

/* Libraries */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>       /* for doing math */
#include <time.h>       /* for working with time */
#include <string.h>     /* for working with strings */

/* Symbolic Constants */

#define TRUE  1         /* boolean value for true */
#define FALSE 0         /* boolean value for false */

#define DATEOPTIONS 7   /* the amount of dates in our prototype dataset */
#define TIMEOPTIONS 2   /* the amount of clock times to choose from */

/* Function Prototypes */

int get_user_input(void);               /* user_com.c */
void select(int*, char**, int);         /* user_com.c */
void show_menu(char**, int);            /* user_com.c */
int input_validation(int*, int);        /* user_com.c */

#endif /* ENERGY_H */
