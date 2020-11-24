/*
 ===============================================================================
 * File: data.c                     Date completed: 16th of November, 2020
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
 * Description: This file manages our data, and is responsible for returning any
 *              data structs.
 ===============================================================================
 */

#include "./H_files/present.h"

void present_price_data(Price_data data)
{
    print_prices(data.today);

    if(data.access_tomorrow)
        print_prices(data.tomorrow);
}

/* If prices are given as an array of doubles */
void print_prices(Energy_data value)
{
    float *prices = value.prices; 
    int i;

    print_date_2(value.date);

    for(i = 0; i < DAY_HOURS; i++)
    {
        if(prices[i] < average_price(prices) || prices[i] < LOW_PRICE)
            printf("%02d:00: %.2lf !!!\n", i, prices[i]);
        else
            printf("%02d:00: %.2lf\n", i, prices[i]);
    }
}

void print_date_2(Date date)
{
    printf("Prices for %d/%d/%d:\n", date.day, date.month, date.year);
}

/* Calculates the average price */
double average_price(float prices[])
{
    double average = 0;
    int i;

    for(i = 0; i < DAY_HOURS; i++)
        average += prices[i];
    
    average = average / DAY_HOURS;

    return average;
}

void graph(float prices[], Date date)
{
    float min_price, max_price, max_y, step;
    float y_axis[Y_AXIS_LENGTH];

    find_extremes(prices, &min_price, &max_price);

    make_y_axis(y_axis, min_price, max_price, &max_y, &step);
    
    round_prices(prices, step);

    make_graph(prices, y_axis, date, max_y, step);
}

void find_extremes(float prices[], float *min_price, float *max_price)
{
    int i;
    *min_price = prices[0], *max_price = prices[0];
    for(i = 0; i < DAY_HOURS; i++)
    {
        if(prices[i] < *min_price)
            *min_price = prices[i];
        else if(prices[i] > *max_price)
            *max_price = prices[i];
    }
}

void make_y_axis(float y_axis[], float min_price, float max_price, float *max_y, float *step)
{
    int i;
    float min_y = (int)(min_price / 1);
    float current_step = 0;

    *max_y = ((int)(max_price / 1) + 1);
    current_step = *max_y;
    *step = (*max_y - min_y) / Y_AXIS_LENGTH;

    for(i = 0; i < Y_AXIS_LENGTH; i++)
    {
        y_axis[i] = current_step;
        current_step -= *step;
    }
}

void round_prices(float prices[], float step)
{   
    int i;

    for(i = 0; i < DAY_HOURS; i++)
        prices[i] = (prices[i] / step) * step;
} 

void make_graph(float prices[], float y_axis[], Date date, float max_y, float step)
{
    int i, j;
    /* We make 24 empty string with 20 characters each and put them in an array.
       Each string works as an hour's y-axis. */ 
    float current_step;
    char points[Y_AXIS_LENGTH] = "                    ";
    char graph_points[DAY_HOURS][Y_AXIS_LENGTH];
    
    for(i = 0; i < DAY_HOURS; i++)
    {
        for(j = 0; j < Y_AXIS_LENGTH; j++)
            graph_points[i][j] = points[j];
    } 

    for(i = 0; i < DAY_HOURS; i++)
    {
        current_step = max_y;
        for(j = 0; j < Y_AXIS_LENGTH; j++)
        {
            if(prices[i] - current_step >= step/2 && prices[i] - current_step <= step)
            {
                graph_points[i][j-1] = '*';
            }
            else if(prices[i] - current_step <= step/2 && prices[i] - current_step >= 0){
                graph_points[i][j] = '*';
            }
            current_step -= step; 
        }
    } 

    print_graph(y_axis, graph_points, date);
}

void print_graph(float y_axis[], char a[DAY_HOURS][Y_AXIS_LENGTH], Date date)
{
    int i, j;
    printf("DKK / kWh %21s ENERGY PRICES %d/%d/%d\n", " ", date.day, date.month, date.year);
    for(i = 0; i < Y_AXIS_LENGTH; i++)
    {
        printf("%.2lf |", y_axis[i]);
        for(j = 0; j < DAY_HOURS; j++)
            printf(" %c ", a[j][i]);
        printf("\n");
    }

    printf(" ... |________________________________________________________________________\n");
    printf("       00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23  HOUR\n");
}