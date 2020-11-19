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
    /* TODO: Instantiate Day struct and pass it to get_user_input */

    get_user_input();

    do_calculations();
}

/* Does the calculations on the received data, takes in a day struct. */
void do_calculations(void)
{
    /* TODO: Add fees */

    float transport_afgifter,elpris,samlet_pris;

    elpris = 0.2464; /* Elpris koster 0.2464kr. eller 24.64øre */
    transport_afgifter  = 1.61; /* transport_afgifter koster 1.61kr/kWh*/
    samlet_pris = 1.86 /*samlet pris i alt */




    present();
}

/* This presents the received data to the user. */
void present(void)
{
    /* TODO: Present the data */
}
