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

    present(data);
}

/* Does the calculations on the received data, takes in a day struct. */
void do_calculations(User_data *data)
{
    int i;    
    
    for (i = 0; i < DAY_HOURS; i++) {
        convert_kwh(&data->today.prices[i]);
        add_fees(&data->today.prices[i]);
        add_vat(&data->today.prices[i]);
        
        convert_kwh(&data->tomorrow.prices[i]);
        add_fees(&data->tomorrow.prices[i]);
        add_vat(&data->tomorrow.prices[i]);
    }
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
    Graph prices = {0};
    Graph co2 = {0};
    
    Tables today_prices = {0};
    Tables today_co2 = {0};

    /*
    
    Graph tomorrow_prices_g = {0};
    Graph tomorrow_co2_g = {0};

    Tables tomorrow_prices_t = {0};
    Tables tomorrow_co2_t = {0};
            
    */

    /* TODO: Present the data */
    graph(data->today.prices, &prices, data->today.date);
    graph(data->today.co2_emissions, &co2, data->today.date);

    present_price_data(&today_prices, &today_co2, data, 0);
    /*if(data->access_tomorrow){
        graph(data->tomorrow.prices, &tomorrow, data->tomorrow.date);
        present_price_data(&tomorrow_prices, &tomorrow_co2,data, 1);
    }*/
    print_graphs(&prices, &co2, data);
    print_tables(&today_prices, &today_co2);

    if (data->access_tomorrow)
    {
        if (want_data_for_tommorow(*data))
        {
            printf("Hell yeah, the user would love to see the data for tomorrow! Imagine some crazy stuff here...\n");
             /* TODO: insert printy spinny stuff here */
        }
        else
        {
            /* TODO: after debugging, this whole else statement can be removed */
            printf("Hell nah, the user would hate to see the data for tomorrow! ...Moving on.\n");
        }
    }
}
