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

/*Lav visning af printf formidling af priser til en functin og kald dem så de står ved siden af hinanden!*/

#include "./H_files/present.h"

void present_price_data(User_data *data, int check)
{
    if(check == 0)
        print_prices(data->today);
    
    if(data->access_tomorrow && check == 0)
        cmpr_tdy_tmrw(data->today.prices, data->tomorrow.prices);

    if(check == 1)
        print_prices(data->tomorrow);
}

/* If prices are given as an array of doubles */
void print_prices(Energy_data value)
{
    float *prices = value.prices; 
    float prices_cheap[DAY_HOURS];
    float average = average_price(prices);
    int i;         

    printf("\n*---------------------------------------------*\n");
    printf("|   The prices are cheap in these intervals   |\n");
    for(i = 0; i < DAY_HOURS; i++)
    {
        if(prices[i] < average)
        {
            prices_cheap[i] = prices[i];
        }
        else
        {
            prices_cheap[i] = 0;
        }
        if(prices_cheap[i] > 0 && i > 5)
        {
            printf("|---------------------------------------------|\n");
            printf("|            %02d:00 -> %.2f DKK/kWh            |\n", i, prices_cheap[i]);
        }
    }
    printf("*---------------------------------------------*\n");
    
    highest_prices(prices);
}

void highest_prices(float prices[])
{
    int i;
    int hour[] = {0, 0, 0};
    for(i = 5; i < DAY_HOURS; i++)
    {
        if(prices[i] > prices[hour[0]]) {
            hour[2] = hour[1];
            hour[1] = hour[0];
            hour[0] = i;
        } else if (prices[i] > prices[hour[1]]){
            hour[2] = hour[1];
            hour[1] = i;
        } else if (prices[i] > prices[hour[2]]){
            hour[2] = i;
        }
    }
    qsort(hour, 3, sizeof(int), compare_intergers);

    printf("\n*---------------------------------------------*\n");
    printf("| The prices are expensive in these intervals |\n");
    for(i = 0; i < 3; i++){
        printf("|---------------------------------------------|\n");
        printf("|            %02d:00 -> %.2f DKK/kWh            |\n", hour[i], prices[hour[i]]);
    }
    printf("*---------------------------------------------*\n");
    
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

void cmpr_tdy_tmrw(float prices_tdy[], float prices_tmrw[])
{
    float relative_devation = (average_price(prices_tmrw) - average_price(prices_tdy)) / average_price(prices_tdy) * 100;
    if(relative_devation > 1)
    {
        printf("\n*---------------------------------------------*\n"
               "|  The price tomorrow is %.2f%% more expensive |\n"
               "*---------------------------------------------*\n\n",relative_devation);
    }
    else if(relative_devation < -1)
    {
        relative_devation *=(-1);
        printf("\n*---------------------------------------------*\n"
               "|     The price tomorrow is %.2f%% cheaper     |\n"
               "*---------------------------------------------*\n\n",relative_devation);
    }
}

/*___________________________________________________________________________________________________________*/

void graph(float prices[], Date date)
{
    float min_price, max_price, max_y, step;
    float y_axis[Y_AXIS_LENGTH];

    find_extremes(prices, &min_price, &max_price);

    make_y_axis(y_axis, min_price, max_price, &max_y, &step);

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

void make_graph(float prices[], float y_axis[], Date date, float max_y, float step)
{
    int i, j;
    /* We make 24 empty string with 20 characters each and put them in an array. 
       Each string works as an hour's y-axis. */ 
    float current_step;
    char points[Y_AXIS_LENGTH] = "                    ";
    char graph_points[DAY_HOURS][Y_AXIS_LENGTH];
    int graph_line[DAY_HOURS];
    
    for(i = 0; i < DAY_HOURS; i++)
    {
        for(j = 0; j < Y_AXIS_LENGTH; j++)
        {
            graph_points[i][j] = points[j];
        }
    }

    for(i = 0; i < DAY_HOURS; i++)
    {
        current_step = max_y;
        for(j = 0; j < Y_AXIS_LENGTH; j++)
        {
            if(prices[i] - current_step >= step/2 && prices[i] - current_step <= step)
            {
                graph_points[i][j-1] = '*';
                graph_line[i] = j-1;
            }
            else if(prices[i] - current_step <= step/2 && prices[i] - current_step >= 0)
            {
                graph_points[i][j] = '*';
                graph_line[i] = j;
            }
            current_step -= step;
        }
    }

    for(i = 0; i < DAY_HOURS; i++)
        {
            if(graph_line[i] < graph_line[i+1])
            {
                graph_points[i][graph_line[i]+1] = '\\';
                graph_points[i][graph_line[i]] = ' ';
            }

            else if(graph_line[i+1] < graph_line[i])
                graph_points[i][graph_line[i]] = '/';

            else
                graph_points[i][graph_line[i]] = '_';
        }

    print_graph(y_axis, graph_points, date);
}

void print_graph(float y_axis[], char a[DAY_HOURS][Y_AXIS_LENGTH], Date date)
{
    int i, j;
    printf("DKK / kWh %21s ENERGY PRICES %d/%d/%d\n", " ", date.day, date.month, date.year);
    for(i = 0; i < Y_AXIS_LENGTH; i++)
    {
        printf("%.2f |", y_axis[i]);
        for(j = 0; j < DAY_HOURS; j++)
            printf(" %c ", a[j][i]);
        printf("\n");
    }

    printf(" ... |________________________________________________________________________\n");
    printf("       00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23  HOUR\n");
}

int compare_intergers(const void* int1, const void* int2){
    return *((int*)int1)-*((int*)int2);
}