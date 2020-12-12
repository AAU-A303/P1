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

#define Y_AXIS_LENGTH 20
#define TABLE_INNER_SIZE 45
#define GRAPH_SIZE 84

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

void present_data(Tables*, Tables*, User_data*, int); /* input: prices, co2, data, today output: none */
void average_values_table(Strings*, float[], int, enum languages);
void highest_values_table(Strings*, float[], int, enum languages);
float average_value(float[]);
void compare_values_table(Strings*, float[], float[], int, enum languages);
int less_than_step(float[], float);

void graph(float[], Graph*, int);
void find_extremes(float[], Graph*);
void make_y_axis(Graph*, int);
void make_graph(float[], Graph*);
void format_graph(Graph*, int[]);

int compare_floats(float, float);
int compare_intergers(const void*, const void*);


int* fill_table_width(char*);
void print_graphs(Graph*, Graph*, Date*, enum languages);
void print_tables(Tables*, Tables*);
void print_table(Strings*, Strings*);
size_t utf8_length(const char*);
#endif /* PRESENT_H */