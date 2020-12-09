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
#include "../libaries/strings.h"
#include "./user_com.h"

#define Y_AXIS_LENGTH 20

typedef struct _Graph {
    float y_axis[Y_AXIS_LENGTH];
    float min_price;
    float max_price;
    float max_y;
    float step;
    Strings graph;
} Graph;

typedef struct _Tables {
    Strings average;
    Strings compare;
    Strings highest;
} Tables;

void present_price_data(Tables* prices, Tables* co2, User_data *data, int check);
void average_prices_table(Strings *table, float prices[]);
void highest_prices_table(Strings *table,float prices[]);
double average_price(float prices[]);
void compare_prices_table(Strings *table, float today[], float tomorrow[]);
int less_than_step(float prices[], float average);

void graph(float prices[], Graph *graph, Date date, int flag_price);
void find_extremes(float prices[], Graph *graph);
void make_y_axis(Graph *graph, int flag_price);
void make_graph(float prices[], Graph *graph, Date date);
void format_graph(Graph *graph, int graph_line[]);

int compare_floats(float f1, float f2);
int compare_intergers(const void* int1, const void* int2);

void print_graphs(Graph *today, Graph *tomorrow, User_data *data);
void print_tables(Tables* prices, Tables* co2);

#endif /* PRESENT_H */
