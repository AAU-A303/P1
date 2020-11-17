/*
 ===============================================================================
 * File: user_com.c             Date completed: 16th of November, 2020
 ===============================================================================
 * Programmers: Anders G.       E-mail: ageert20@student.aau.dk
 *              Christoffer J.          cjanss20@student.aau.dk
 *              Dennis L.               dbla19@student.aau.dk
 *              Jamie H.                jhamme20@student.aau.dk
 *              Loke W.                 lwalst20@student.aau.dk
 *              Mads L.                 mlundf20@student.aau.dk
 *              Master P.               mprase20@student.aau.dk
 ===============================================================================
 * Study Group: A303
 * Supervisor: Kamal Shahid     Class: P1, Computer Science - Fall Semester
 ===============================================================================
 * Description: This is a file to manage all communication with the user.
 ===============================================================================
 */

#include "energy.h"

/* FOR DEBUGGING ONLY!!! TODO: DELETE WHEN IMPLEMENTED */
int main (void)
{
    do {
        get_user_input();
    } while (has_new_inquiry());
    
    return EXIT_SUCCESS;
}

/* Gets the user input for date and time. */
void get_user_input(void)
{
    int day, month, year = CURRENT_YEAR;
    int hour;
    
    set_date(&day, &month, year);
    printf("\nThe chosen date is: %.02d/%.02d, %d\n", day, month, year);
    
    set_time(&hour);
    printf("\nAccording to the chosen time, the clock is: %.02d:00\n", hour);
    
    if (hour > DAY_AHEAD)
    {
        /* TODO: If so, set is_available of the struct to TRUE */
        /* TODO: Populate the day_ahead array with the data for the next day */
        printf("\nDay Ahead prices are available!\n");
    }
    else
    {
        /* TODO: Else, set is_available of the struct to FALSE */
        printf("\nDay Ahead prices are NOT yet available...\n");
    }
}

/* Set the temp date for the prototype */
void set_date(int *day, int *month, int year)
{
    int is_valid = FALSE;
    
    do {
        printf("Please enter the current date (DD/MM format): ");
        scanf(" %d/%d", day, month);
        
        /* TODO: remove the first two if statements after Jan 1st */
        if(*month <= 11)
        {
            if (*month == 11 && *day > 5) { continue; }
            
            if (*day <= days_in_month(*month, CURRENT_YEAR) && *day > 0)
                {is_valid = TRUE;
        }
    } while (!is_valid);
}

/* Set the temp time for the prototype */
void set_time(int *hour)
{
    int is_valid = FALSE;
    
    do {
        printf("Please enter the current hour (HH format): ");
        scanf(" %d", hour);
        if(*hour < DAY_HOURS && *hour >= 0) is_valid = TRUE;
    } while (!is_valid);
}

/* Checks and returns the amount of days in the currently selected month */
int days_in_month(int month, int year)
{
    int days;
    switch(month){
        case JAN: case MAR: case MAY: case JUL: case AUG: case OCT: case DEC:
            days = 31; break;
        case APR: case JUN: case SEP: case NOV:
            days = 30; break;
        case FEB:
            if (is_leap_year(year)) days = 29; else days = 28; break;
        default: exit(-1);
    }
    return days;
}

/* Checks and returns whether the current year is a leap year or not */
int is_leap_year(int year)
{
    if (year % 400 == 0) return TRUE;
    else if (year % 100 == 0) return FALSE;
    else if (year % 4 == 0) return TRUE;
    else return FALSE;
}

/* Returns whether the user wants to check another day or exit the programme */
int has_new_inquiry()
{
    char input;
    int wrong_input = TRUE;
    
    do
    {
        printf("\nWould you like to check another day? Enter Y or N> ");
        scanf(" %c", &input);
        
        if ((input != 'y') || (input != 'Y') ||
            (input != 'n') || (input != 'N')) { wrong_input = FALSE; }
    } while (wrong_input);
    
    printf("\n"); return (input == 'y' || input == 'Y');
}
