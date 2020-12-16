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
char* language_names[] = {"English","Dansk"};

/* Sets up the data file according to user input. */
void setup_user_data(User_data *data)
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

    print_string_from_id(data->language, "Supported_languages", 1);
    for(i = 0; i < language_count; i++){
        printf("\t%d: %s\n", i, language_names[i]);
    }
    do {
        print_string_from_id(data->language, "Select_language", 0);
        if(scanf(" %d", &answer) != 1)
        {
            print_string_from_id(data->language, "Fail_message_language", 1);
            printf("\n"); fflush(stdin);
        }
        else
        {
            if(answer >= 0 && answer < language_count) { is_valid = TRUE; }
            else
            {
                print_string_from_id(data->language, "Fail_message_language", 1);
                printf("\n");
                
            }
        }
    } while(!is_valid);

    data->language = answer;
}

/* Set the temp date for the prototype. */
void set_date(User_data *data)
{
    int is_valid = FALSE;
    int day, month, year = CURRENT_YEAR;
    
    do {
        print_string_from_id(data->language, "Select_date", 0);
        
        if(scanf(" %d/%d", &day, &month) != 2)
        {
            print_string_from_id(data->language, "Fail_message_general", 1); printf("\n");
            fflush(stdin);
        }
        else
        {
            /* TODO: remove the first two if statements after Jan 1st */
            if(month <= 11)
            {
                if (month == 11 && day > 5) { continue; }

                if (day <= days_in_month(month, CURRENT_YEAR) && day > 0) { is_valid = TRUE; }
                else { print_string_from_id(data->language, "Fail_message_general", 1); printf("\n"); }
            }
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
        if(scanf(" %d", hour) != 1)
        {
            print_string_from_id(data->language, "Fail_message_general", 1); printf("\n");
            fflush(stdin);
        }
        else{
            if(*hour < DAY_HOURS && *hour >= 0){ is_valid = TRUE; }
            else { print_string_from_id(data->language, "Fail_message_general", 1); printf("\n"); }
        }
    } while (!is_valid);
}

/* Checks and returns the amount of days in the currently selected month. */
int days_in_month(int month, int year)
{
    switch(month){
        case JAN: case MAR: case MAY: case JUL: case AUG: case OCT: case DEC: return 31; break;
        case APR: case JUN: case SEP: case NOV: return 30; break;
        case FEB: if (is_leap_year(year)) return 29; else return 28; break;
        default: exit(-1);
    }
}

/* Checks and returns whether the current year is a leap year or not. */
int is_leap_year(int year)
{
    if (year % 400 == 0) return TRUE;
    else if (year % 100 == 0) return FALSE;
    else if (year % 4 == 0) return TRUE;
    else return FALSE;
}

/* Returns whether the user wants to see the data for tomorrow, when it is available. */
int want_data_for_tommorow(User_data data)
{
    char input;
    int wrong_input = TRUE;
    
    do
    {
        printf("\n"); print_string_from_id(data.language, "Tomorrow", 0);
        scanf(" %c", &input);
        
        if ((input == 'y') || (input == 'Y') ||
            (input == 'n') || (input == 'N')) { wrong_input = FALSE; }
    } while (wrong_input);
    
    printf("\n"); return (input == 'y' || input == 'Y');
}

/* Returns whether the user wants to check another day or exit the programme. */
int has_new_inquiry(User_data data)
{
    char input;
    int wrong_input = TRUE;
    
    do
    {
        printf("\n"); print_string_from_id(data.language, "Continue", 0);
        scanf(" %c", &input);
        
        if ((input == 'y') || (input == 'Y') ||
            (input == 'n') || (input == 'N')) { wrong_input = FALSE; }
    } while (wrong_input);
    system("cls || clear"); return (input == 'y' || input == 'Y');
}
