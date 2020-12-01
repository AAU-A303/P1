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

#ifndef PRESENT_H
#define PRESENT_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "data.h"
#include "present.h"

#define LOW_PRICE 4
#define Y_AXIS_LENGTH 20

void present_price_data(Price_data data);
void print_prices(Energy_data prices);
void print_date_2(Date date);
double average_price(float prices[]);
void print_price_string(char intput_data_1[]);

void graph(float prices[], Date date);
void find_extremes(float prices[], float *min_price, float *max_price);
void make_y_axis(float y_axis[], float min_price, float max_price, float *max_y, float *step);
void make_graph(float prices[], float y_axis[], Date date, float max_y, float step);
void format_graph(char graph_points[DAY_HOURS][Y_AXIS_LENGTH], int graph_line[]);
void print_graph(float y_axis[], char a[DAY_HOURS][Y_AXIS_LENGTH], Date date);

#endif /* PRESENT_H */
