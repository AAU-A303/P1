/*
 ===============================================================================
 * File: user_com.c                 Date completed: 16th of November, 2020
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
 * Description: This is a file to manage all communication with the user.
 ===============================================================================
 */

#include "./H_files/user_com.h"

/* Constants */
char* language_names[] = {"English","Dansk","Française","Suomen kieli"};

/* Gets the user input for date and time. */
void get_user_input(User_data *data)
{
    int hour;

    set_language(data);
    set_date(data);
    set_time(&hour, data);

    get_data(data, data->today.date);
    
    if (hour >= DAY_AHEAD) { data->access_tomorrow = TRUE; }
    else { data->access_tomorrow = FALSE; }
}

/* Set the language for the prototype. */
void set_language(User_data *data)
{
    int is_valid = FALSE;
    int answer = -1;
    int i = 0;
    char language[128];

    print_string_from_id(data->language, "Supported_languages", 1);
    for(i = 0; i < language_count; i++){
        sprintf(language, "\t%d: %s\n", i, language_names[i]);
        print_string(language, 0);
    }
    do {
        print_string_from_id(data->language, "Select_language", 0);
        scanf(" %d", &answer);
        if(answer >= 0 && answer < language_count)
            is_valid = TRUE;
    } while (!is_valid);

    data->language = answer;
}

/* Set the temp date for the prototype. */
void set_date(User_data *data)
{
    int is_valid = FALSE;
    int day, month, year = CURRENT_YEAR;
    
    do {
        print_string_from_id(data->language, "Select_date", 0);
        /* printf("Please enter the current date (DD/MM format)> "); */
        scanf(" %d/%d", &day, &month);
        
        /* TODO: remove the first two if statements after Jan 1st */
        if(month <= 11)
        {
            if (month == 11 && day > 5) { continue; }
            
            if (day <= days_in_month(month, CURRENT_YEAR) && day > 0)
                is_valid = TRUE;
        }
    } while (!is_valid);

    data->today.date.day = day; 
    data->today.date.month = month; 
    data->today.date.year = year;
}

/* Set the temp time for the prototype. */
void set_time(int *hour, User_data *data)
{
    int is_valid = FALSE;
    
    do {
        print_string_from_id(data->language, "Select_hour", 0);
        /* printf("Please enter the current hour (HH format)> "); */
        scanf(" %d", hour);
        if(*hour < DAY_HOURS && *hour >= 0) is_valid = TRUE;
    } while (!is_valid);
}

/* Checks and returns the amount of days in the currently selected month. */
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

/* Checks and returns whether the current year is a leap year or not. */
int is_leap_year(int year)
{
    if (year % 400 == 0) return TRUE;
    else if (year % 100 == 0) return FALSE;
    else if (year % 4 == 0) return TRUE;
    else return FALSE;
}

/* Returns whether the user wants to check another day or exit the programme. */
int has_new_inquiry(User_data data)
{
    char input;
    int wrong_input = TRUE;
    
    do
    {
        print_string_from_id(data.language, "Continue", 0);
        /* printf("\nWould you like to check another day? Enter Y or N> "); */
        scanf(" %c", &input);
        
        if ((input != 'y') || (input != 'Y') ||
            (input != 'n') || (input != 'N')) { wrong_input = FALSE; }
    } while (wrong_input);
    
    printf("\n"); return (input == 'y' || input == 'Y');
}
