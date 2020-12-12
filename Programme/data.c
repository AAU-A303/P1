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
#include <stdio.h>

/* Gets needed data from our dataset based on a given date in the dataset. */
void get_data(User_data *user_data, Date target_date)
{
    float current_price;
    float current_co2_emission;
    char date_string[64];
    int index_today = 0, index_tomorrow = 0, scan_res = 0;
    Date current_date = {0};
    Energy_data today = {0};
    Energy_data tomorrow = {0};
    FILE* file;
    /*
        "fopen" opens a file given a "DATA_FILE" and the "mode" of which to open the file.
        In this case, we just need to read the file so we use the "r" mode.
        ("r" = read), ("w" = write), ("a" = append) and ("+" = update). These modes can be combined with each other.
    */
    file = fopen(DATA_FILE, "r");
    /*
        If the "file" is "NULL", then we were unable to either find or open the file.
    */
    if(file != NULL)
    {
        /*
            While there's still a new line, fill the char array with its contents.
        */
        while (scan_res != -1) {
            /*
                split up the line into the format:
                char[]: "string_date", float: "current_price" and float: "current_co2_emission";
            */
            scan_res = fscanf(file, "%s %f %f", date_string, &current_price, &current_co2_emission);
            /*
                Check if we havent scanned in the correct amount of items and if we havent reached the end of the file.
                If both are true we print an error message. 
            */
            if(scan_res != 3 && scan_res != -1)
                printf("Incorrectly formatted dataset: %s\n", DATA_FILE);
            /*
                split up the "date_string" int to the format:
                int: day
                int: month
                int: year
            */
            date_set(&current_date, date_string);
            /*
                First, we check if the "current_date" is equal to the "target_date".
                If the two dates are equal we set "today.date" to the current_date
                and we add the "current_price" and "today.co2_emissions" to the "today.price"
                and "today.co2_emissions" arrays at the "index_today".
                If the check fails we check if its the next day instead.
                And if it is the next day we set the "tomorrow.date" and "tomorrow.price" at "index_tomorrow".
            */
            if(date_equals(&current_date, &target_date))
            {
                date_set(&today.date, date_string);
                today.prices[index_today] = current_price;
                today.co2_emissions[index_today] = current_co2_emission;
                index_today++;
            }
            else if(date_difference_in_days(&target_date, &current_date) == 1)
            {
                date_set(&tomorrow.date, date_string);
                tomorrow.prices[index_tomorrow] = current_price;
                tomorrow.co2_emissions[index_tomorrow] = current_co2_emission;
                index_tomorrow++;
            }
        }
    } 
    else { printf("Failed to open file \"%s\"\n\n", DATA_FILE); }
    /*
        Now that we have populated the "Energy_data" struct "today" and "tomorrow".
        we can add them to "user_data->today" and "user_data->tomorrow".
    */
    user_data->today = today;
    user_data->tomorrow = tomorrow;
    /*
        It's important to remember to close the file after opening it.
        The result of not closing the file is that both other programs and this program
        will be unable to open the file again until this program exits.
    */
    fclose(file);
}

/* Fills a given date struct based on a date string */
void date_set(Date *date, char date_string[])
{
    sscanf(date_string, "%d/%d/%d", &date->day, &date->month, &date->year);
}

/* Calculates the diffrence between two given dates */
int date_difference_in_days(Date *date_a, Date *date_b)
{
    struct tm current_date = { 0 };
    struct tm next_date = { 0 };
    double current_date_seconds;
    double next_date_seconds;
    /*
        Add out date values to the tm struct.
        We subtract 1900 from the year since tm_year is specified by the years since 1900.
        We subtract 1 from the month since tm_month is int the range 0-11.  
    */
    current_date.tm_year = date_a->year - 1900;
    current_date.tm_mon = date_a->month - 1;
    current_date.tm_mday = date_a->day;

    next_date.tm_year = date_b->year - 1900;
    next_date.tm_mon = date_b->month - 1;
    next_date.tm_mday = date_b->day;

    current_date_seconds = mktime(&current_date);
    next_date_seconds = mktime(&next_date);

    return (next_date_seconds - current_date_seconds) / DAY_IN_SECONDS; 
}

/* Checks if two given dates are equal */
int date_equals(Date *date_a, Date *date_b)
{
    if(date_a->year == date_b->year)
    {
        if(date_a->month == date_b->month)
        {
            if(date_a->day == date_b->day)
            {
                return TRUE;
            }
        }
    } return FALSE;
}

/* Resets the values in a given Energy_data struct */
void reset_energy_data(Energy_data *energy_data)
{
    int i = 0;
    energy_data->date.year = 0;
    energy_data->date.month = 0;
    energy_data->date.day = 0;
    for(i = 0; i < DAY_HOURS; i++){
        energy_data->prices[i] = 0;
        energy_data->co2_emissions[i] = 0;
    }
}