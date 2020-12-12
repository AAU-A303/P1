/*
 ===============================================================================
 * File: cutest.h                   Date completed: 16th of November, 2020
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
#ifndef CUTEST_H
#define CUTEST_H

#include <stdlib.h>
#include <stdio.h>
#include "../libaries/CuTest.h"
#include "data.h"
#include "energy.h"
#include "localisation.h"

void all_tests();                               /* input: none, output: none */
CuSuite* test_suite();                          /* input: none, output: CuSuite */
void test_load_data(CuTest*);                   /* input: test_context, output: none */
void test_convert_kwh(CuTest*);                 /* input: test_context, output: none */
void test_add_fees(CuTest*);                    /* input: test_context, output: none */
void test_add_vat(CuTest*);                     /* input: test_context, output: none */
void test_do_calculations(CuTest*);             /* input: test_context, output: none */
void test_get_localisation_indexes(CuTest*);    /* input: test_context, output: none */
void test_get_string_from_id(CuTest*);          /* input: test_context, output: none */
void test_utf8_length(CuTest*);                 /* input: test_context, output: none */
void test_fill_table_width(CuTest*);            /* input: test_context, output: none */
void test_average_price(CuTest*);               /* input: test_context, output: none */
void test_find_extremes(CuTest*);               /* input: test_context, output: none */

#endif /* CUTEST_H */