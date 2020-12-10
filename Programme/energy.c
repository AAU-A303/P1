/*
 ===============================================================================
 * File: energy.c                   Date completed: 16th of November, 2020
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

    present(data, 1);

    if (data->access_tomorrow && want_data_for_tommorow(*data))
        present(data, 0);
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
void present(User_data *data, int today){
    Graph prices_graph = {0};
    Graph co2_graph = {0};

    Tables prices_table = {0};
    Tables co2_table = {0};
    if(today){
        graph(data->today.prices, &prices_graph, 1);
        graph(data->today.co2_emissions, &co2_graph,  0);
        
        present_data(&prices_table, &co2_table, data, today);

        print_graphs(&prices_graph, &co2_graph, &data->today.date, data->language);
        print_tables(&prices_table, &co2_table);
    } else {
        graph(data->tomorrow.prices, &prices_graph, 1);
        graph(data->tomorrow.co2_emissions, &co2_graph,  0);

        present_data(&prices_table, &co2_table, data, today);
        
        print_graphs(&prices_graph, &co2_graph, &data->tomorrow.date, 1);
        print_tables(&prices_table, &co2_table);
    }
    free_strings(&prices_table.average);
    free_strings(&prices_table.highest);
    free_strings(&prices_table.compare);
    free_strings(&prices_graph.graph);
    free_strings(&co2_graph.graph);
}
