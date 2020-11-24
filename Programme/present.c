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

#include "./H_files/data.h"

#define LOW_PRICE 4

void present_price_data(Price_data data);
void print_prices(Energy_price prices);
void print_date(Date date);
double average_price(float prices[]);
void print_price_string(char intput_data_1[]);

/* for debugging */
int main(void)
{
    /*double input_data[DAY_HOURS] = {2.01, 3.05, 6.91, 9.99, 7.10, 8.24,
                                    2.01, 3.05, 6.91, 9.99, 7.10, 8.24,
                                    2.01, 3.05, 6.91, 9.99, 7.10, 8.24,
                                    2.01, 3.05, 6.91, 9.99, 7.10, 8.24};*/
    
    /*char input_data_1[120] = "2.01 3.05 6.91 9.99 7.10 8.24 2.01 3.05 6.91 9.99 7.10 8.24 2.01 3.05 6.91 9.99 7.10 8.24 2.01 3.05 6.91 9.99 7.10 8.24";*/

    /*print_price_double(input_data);
    print_price_string(input_data_1);*/

    return EXIT_SUCCESS; 
}

/* If prices are given as an string */
/* void print_price_string(char intput_data_1[])
{
    int i = 0, k = 0;
    char prices[120];

    for(k = 0; k < DAY_HOURS; k++)
    {
        while(!isspace(intput_data_1[i++]))
        strncpy(prices, intput_data_1, i);
        prices[i - 1] = '\0';
        intput_data_1 += i;
        i = 0;

        printf("The electricity price for %02d:00 is %s\n", k, prices);
    }
}
*/

/* CHECK THIS OUT */
void present_price_data(Price_data data)
{
    print_prices(data.today);

    if(data.access_tomorrow)
        print_prices(data.tomorrow);
}

/* If prices are given as an array of doubles */
void print_prices(Energy_price value)
{
    float *prices = value.prices; 
    int i;

    print_date(value.date);

    for(i = 0; i < DAY_HOURS; i++)
    {
        if(prices[i] < average_price(prices) || prices[i] < LOW_PRICE)
            printf("%02d:00: %.2lf !!!\n", i, prices[i]);
        else
            printf("%02d:00: %.2lf\n", i, prices[i]);
    }
}

void print_date(Date date)
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

/** below function will need a struct of type "data" and a member "time" */


void CheckpriceNightTime(Day_or_night time)
{   /*nighttime is defined as between 00:00 and 07:00 am*/
    /*load in a struct with the given parameter "time"*/
  
    if(time.night >= 0.00 && time.night <= 7.00) 
    {
         
    }
}

void CheckpriceDayTime(Day_or_night day)
{   /*daytime is defined as between 07:00 am to 23:00 pm*/
    /*load in a struct with the given parameter "time"*/
   Day_or_night time;
    if(time.day >= 7.00 && time.day <= 0.00) 
    {
        
    }
   
    
}
