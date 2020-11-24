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
void setup(User_data *data)
{    
    reset_energy_price(&data->today);
    reset_energy_price(&data->tomorrow);

    get_user_input(data);
    
    do_calculations(data);
}

/* Does the calculations on the received data, takes in a day struct. */
void do_calculations(User_data *data)
{
    int i;    
    
    for (i = 0; i < DAY_HOURS; i++) {
        convert_kwh(&data->today.prices[i]); add_fees(&data->today.prices[i]);
        
        convert_kwh(&data->tomorrow.prices[i]);
        add_fees(&data->tomorrow.prices[i]);
    }

    present(data);
}

/* This is responsible for coverting the current price to kwh */
void convert_kwh(float *price) { *price = *price / MWH_TO_KWH; }

/* This is responsible for adding the fees to the current price */
void add_fees(float *price) { *price += TRANSPORT_FEE; }

/* This is responsible for adding the VAT to the current price */
void add_vat(float *price) { *price = *price * VAT; }

/* This presents the received data to the user. */
void present(User_data *data)
{
    /* TODO: Present the data */
    print_user_data(*data);
}
