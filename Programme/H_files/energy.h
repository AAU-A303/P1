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
#include "user_com.h"
/* Symbolic Constants */

#define TRUE  1                 /* boolean value for true */
#define FALSE 0                 /* boolean value for false */

/* Function Prototypes */

void setup(void);               /* input: none, output: none */
void do_calculations(void);     /* input: none, output: none */
void present(void);             /* input: none, output: none */

#endif /* ENERGY_H */
