/*
 ===============================================================================
 * File: main.c                     Date completed: 16th of November, 2020
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
 * Description: This is the main file, from here the entire programme is run and
 *              maintained.
 ===============================================================================
 */

#include "./H_files/user_com.h"
#include "./H_files/energy.h"

int main(void)
{
    User_data data = { 0 };
    printf("\nWelcome...\n");
    
    do {
        setup(&data);
    } while (has_new_inquiry(data));
    
    printf("Thank you for trying out our prototype!\n");

    return EXIT_SUCCESS;
}
