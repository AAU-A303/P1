/*
 ===============================================================================
 * File: energy.c                   Date completed: 16th of November, 2020
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
 * Description: This is responsible for managing most of our logic of this
 *              programme.
 ===============================================================================
 */

#include "./H_files/energy.h"

/* Responsible for doing all of the calculations. */
void setup(void)
{
    Price_data data = { 0 };

    get_user_input(&data);
    
    do_calculations(&data);
}

/* Does the calculations on the received data, takes in a day struct. */
void do_calculations(Price_data *data)
{
    /* TODO: Add fees */
    
    present();
}

/* This presents the received data to the user. */
void present()
{
    /* TODO: Present the data */
}
