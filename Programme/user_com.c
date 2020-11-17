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

int main (void)
{
    get_user_input();
}

/* Gets the user input and responsible for creating the structs for today and
   tomorrow, accordingly. */
int get_user_input(void)
{
    int date = -1, time = -1;
    
    char *date_menu[DATEOPTIONS] = {"Thursday the 22nd of October",
                                    "Friday the 23rd of October",
                                    "Saturday the 24th of October",
                                    "Sunday the 25th of October",
                                    "Monday the 26th of October",
                                    "Tuesday the 27th of October",
                                    "Wednesday the 28th of October"};
    char *time_menu[TIMEOPTIONS] = {"10:00 before noon",
                                    "15:00 after noon"};
    
    printf("\nFirst you need to specify a date:\n");
    select(&date, date_menu, DATEOPTIONS);
    
    printf("\nNow, you need to specify a time:\n");
    select(&time, time_menu, TIMEOPTIONS);

    return EXIT_SUCCESS;
}

/* Select date and time. */
void select(int *choice, char **menu, int size)
{
    show_menu(menu, size);
    printf("Please choose one of the indexes from above> ");
    
    input_validation(choice, size - 1);
    
    if (size == DATEOPTIONS)
    {
        printf("\nThe chosen date is: ");
        switch (*choice) {
            case 0: case 1: case 2: case 3: case 4: case 5: case 6:
                printf("\n%s\n", menu[*choice]); break;
                
            default: printf("not valid..."); break;
        }
    }
    else
    {
        printf("\nThe chosen time is: ");
        switch (*choice) {
            case 0: case 1: printf("\n%s\n", menu[*choice]); break;
                
            default: printf("not valid..."); break;
        }
    }
}

/* Responsible for showing the currently available menu options. */
void show_menu(char **array, int size)
{
    int i;
    
    for (i = 0; i < size; i++) { printf("%d: %s\n", i, array[i]); }
}

/* Checks the input from the user and validates the selected choice. */
int input_validation(int *input, int max)
{
    do { scanf("%d", input); } while (*input > max || *input < 0);
}

/* TODO: Create a function to construct a struct for any given day */

/* TODO: Call said function from the switches in select */
