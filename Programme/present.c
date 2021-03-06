/*
 ===============================================================================
 * File: present.c                  Date completed: 12th of December, 2020
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
 * Description: This file manages the logic for presenting the data to the user
 *              by constructing graphs and tables.
 ===============================================================================
 */

#include "./H_files/present.h"

/* Handles the core logic of presenting the data */
void present_data(Tables* prices, Tables* co2, User_data* data, int today)
{
    Energy_data target = today ? data->today : data->tomorrow;
    average_values_table(&(prices->average), target.prices, 1, data->language);
    average_values_table(&(co2->average), target.co2_emissions, 0, data->language);

    highest_values_table(&prices->highest, target.prices, 1, data->language);
    highest_values_table(&co2->highest, target.co2_emissions, 0, data->language);

    if(data->access_tomorrow && today){

        compare_values_table(&prices->compare, target.prices, data->tomorrow.prices, 1, data->language);
        compare_values_table(&co2->compare, target.co2_emissions, data->tomorrow.co2_emissions, 0, data->language);
    }
}

/* If prices are given as an array of floats */
void average_values_table(Strings *table, float values[], int is_prices, enum languages language)
{
    float values_low[DAY_HOURS];
    float average = average_value(values);
    int hour_1 = 0, hour_2 = 0;
    int i, *length;

    char* header;
    
    if(is_prices){
        header = get_string_from_id(language, "Table_prices_low");
    } else {
        header = get_string_from_id(language, "Table_CO2_low");
    }
    length = fill_table_width(header);


    strings_append(table, "╭─────────────────────────────────────────────╮");
    strings_append_format(table, "│%*s%s%*s│", length[0], "", header, length[1],
                          "");
    
    for(i = 0; i < DAY_HOURS; i++)
    {
        if(values[i] < average)
        {
            values_low[i] = values[i]; 
        }
        else
        {
            values_low[i] = 0;
        }
        if(values_low[i] > 0)
        {   
            hour_1 = i;
            while(i < DAY_HOURS){
                if(compare_floats(values[hour_1], values[i+1])){
                    hour_2 = i+1;
                    i = hour_2;
                } else{
                    break;
                }
            }
            if(hour_2 > hour_1){
                strings_append(table, "├─────────────────────────────────────────────┤");
                strings_append_format(table,
                    "│    %02d:00 - %02d:00 -> % 3.2f %*s           │", 
                    hour_1,
                    hour_2,
                    values_low[hour_1],
                    values_low[hour_1] >= 100 ? 5 : 6,
                    is_prices ? "DKK/kWh" : "g/kWh");
            } else {
                strings_append(table, "├─────────────────────────────────────────────┤");
                strings_append_format(table,
                    "│            %02d:00 -> % 3.2f %*s           │",
                    hour_1,
                    values_low[hour_1],
                    values_low[hour_1] >= 100 ? 5 : 6,
                    is_prices ? "DKK/kWh" : "g/kWh");
            }
        }
    }
    strings_append(table, "╰─────────────────────────────────────────────╯");
    free(length);
    free(header);
}


/* Handles the logic of the highest prices table. */
void highest_values_table(Strings *table, float values[], int is_prices, enum languages language)
{
    int i, *length;
    int hour[] = {-1, -1, -1};
    float average = average_value(values);
    char* header;
    for(i = 0; i < DAY_HOURS; i++)
    {   
        if(hour[0] == -1) { hour[0] = i; }
        else if(hour[1] == -1) { hour[1] = i; }
        else if(hour[2] == -1) { hour[2] = i; }

        if(values[i] > values[hour[0]])
        {
            hour[2] = hour[1]; hour[1] = hour[0]; hour[0] = i;
        }
        else if (hour[1] != -1 && values[i] > values[hour[1]])
        {
            hour[2] = hour[1]; hour[1] = i;
        }
        else if (hour[2] != -1 && values[i] > values[hour[2]])
        {
            hour[2] = i;
        }
    }

    qsort(hour, 3, sizeof(int), compare_intergers);

    if(less_than_step(values, average))
    { 
        if(is_prices){
            header = get_string_from_id(language, "Table_prices_neutral");
        } else {
            header = get_string_from_id(language, "Table_CO2_neutral");
        }
            
        length = fill_table_width(header);
        strings_append(table, "╭─────────────────────────────────────────────╮");
        strings_append_format(table,
                              "│%*s%s%*s│",length[0], "", header, length[1], "");
        strings_append(table, "╰─────────────────────────────────────────────╯");
    }
    else
    {
        if(is_prices){
            header = get_string_from_id(language, "Table_prices_high");
        } else {
            header = get_string_from_id(language, "Table_CO2_high");
        }
        
        length = fill_table_width(header);
        
        strings_append_format(table,
                              "╭─────────────────────────────────────────────╮");
        strings_append_format(table,
                              "│%*s%s%*s│",length[0], "", header, length[1], "");
        for(i = 0; i < 3; i++)
        {
            strings_append(table,
                           "├─────────────────────────────────────────────┤");
            strings_append_format(table,
                "│            %02d:00 ─> %3.2f %*s            │",
                hour[i],
                values[hour[i]],
                values[hour[i]] >= 100 ? 5 : 6,
                is_prices ? "DKK/kWh": "g/kWh");
        }
        strings_append(table, "╰─────────────────────────────────────────────╯");
    }
    free(length);
    free(header);
}

/* Calculates and returns the average values of the day */
float average_value(float values[])
{
    float average = 0;
    int i;
    for(i = 0; i < DAY_HOURS; i++)
        average += values[i];
    
    average = average / DAY_HOURS;

    return average;
}


/* Handles the logic of the compare prices table. */
void compare_values_table(Strings *table, float today[], float tomorrow[], int is_prices, enum languages language)
{
    float relative_deviation = (average_value(tomorrow) - average_value(today)) / average_value(today) * 100;
    char* header = {0};
    char* body = {0};
    int* length = {0};

    if(relative_deviation > 1)
    {
        if(is_prices){
            header = get_string_from_id(language, "Price_compare_positive");
        } else {
            header = get_string_from_id(language, "CO2_compare_positive");
        }

        body = calloc(strlen(header)*2, sizeof(char));
        sprintf(body, header, relative_deviation);
        length = fill_table_width(body);
        
        strings_append(table, "╭─────────────────────────────────────────────╮");
        strings_append_format(table, 
            "|%*s%s%*s|", length[0], "", body, length[1], "");
        strings_append(table, "╰─────────────────────────────────────────────╯");
    }
    else if(relative_deviation < (-1))
    {
        relative_deviation *= (-1);

        if(is_prices){
            header = get_string_from_id(language, "Price_compare_negative");
        } else {
            header = get_string_from_id(language, "CO2_compare_negative");
        }

        body = calloc(strlen(header)*2, sizeof(char));
        sprintf(body, header, relative_deviation);
        length = fill_table_width(body);

        strings_append(table, "╭─────────────────────────────────────────────╮");
        strings_append_format(table,
            "|%*s%s%*s|", length[0], "", body, length[1], "");
        strings_append(table, "╰─────────────────────────────────────────────╯");
    }
    free(length);
    free(body);
    free(header);
}

/* Handles the creation of a graph. */
void graph(float values[], Graph *graph, int is_price)
{
    find_extremes(values, graph);
    make_y_axis(graph, is_price);
    make_graph(values, graph);
}

/* Finds the lowest and highest points of the graph. */
void find_extremes(float values[], Graph *graph)
{
    int i;
    graph->min_value = values[0];
    graph->max_value = values[0];
    for(i = 0; i < DAY_HOURS; i++)
    {
        if(values[i] < graph->min_value){
            graph->min_value = values[i];
        }
        else if(values[i] > graph->max_value){
            graph->max_value = values[i];
        }
    }
}

/* Creates the y-axis of the graph. */
void make_y_axis(Graph *graph, int is_price)
{
    int i;
    float min_y, current_step = 0;

    if(is_price)
    {
        min_y = ((double)((int)(graph->min_value * 2))) / 2;
        graph->max_y = ((double)((int)((graph->max_value + 0.5) * 2))) / 2;
    }
    else
    {
        min_y = (int)(graph->min_value / 50) * 50;
        graph->max_y = (int)((graph->max_value + 50) / 50) * 50;
    }

    current_step = graph->max_y;
    graph->step = (graph->max_y - min_y) / Y_AXIS_LENGTH;

    for(i = 0; i < Y_AXIS_LENGTH; i++)
    {
        graph->y_axis[i] = current_step;
        current_step -= graph->step;
    }
}

/* Responsible for making the graph. */
void make_graph(float values[], Graph *graph)
{
    int i, j, is_set = 0;
    /* We make 24 empty string with 20 characters each and put them in an array. 
       Each string works as an hour's y-axis. */ 
    float current_step;
    int graph_line[DAY_HOURS] = {0};

    for(i = 0; i < DAY_HOURS; i++)
    {
        current_step = graph->max_y;
        for(j = 0; j < Y_AXIS_LENGTH; j++)
        {
            if(values[i] - current_step >= graph->step / 2 && values[i] -
               current_step <= graph->step)
            {
                graph_line[i] = j-1;
                is_set = 1;
            }

            else if(values[i] - current_step <= graph->step / 2 && values[i] -
                    current_step >= 0)
            {
                graph_line[i] = j;
                is_set = 1;
            }
            current_step -= graph->step;
        }
        if(is_set == 0){ graph_line[i] = j - 1; }
        else { is_set = 0; }
    }

    format_graph(graph, graph_line);
}

/* Responsible for formatting the graph. */
void format_graph(Graph *graph, int graph_line[])
{
    int i;
    char temp[] = "                    ";
    for(i = 0; i < DAY_HOURS; i++)
    {
        if(graph_line[i] < graph_line[i+1])
        {
            temp[graph_line[i]+1] = '\\';
            temp[graph_line[i]] = ' ';
        }

        else if(graph_line[i+1] < graph_line[i]){
           temp[graph_line[i]] = '/';
        }
        else {
            temp[graph_line[i]] = '_';
        }
        strings_append_format(&(graph->graph),"%s", temp);
        strcpy(temp, "                    ");
    }
}

/* Responsible for printing the graph to the screen. */
void print_graphs(Graph *today, Graph *tomorrow, Date *date,
 enum languages language)
{
    int i, j;
    char* co2_header;
    char* prices_header;
    char* hour;
    prices_header = get_string_from_id(language, "Graph_price");
    co2_header = get_string_from_id(language, "Graph_CO2");
    hour = get_string_from_id(language, "Time");
    printf("\nDKK / kWh %21s %12s%d/%d/%d", " ", prices_header, date->day,
           date->month, date->year);
    printf("%33sg / kWh %21s %12s%d/%d/%d\n", " ", "", co2_header, date->day,
           date->month, date->year);
    for(i = 0; i < Y_AXIS_LENGTH; i++)
    {
        printf("%.2f │", today->y_axis[i]);
        for(j = 0; j < DAY_HOURS; j++)
        {
            printf(" %c ", today->graph.buffer[j][i]);
        }
        printf("          ");
        printf("%3.0f │", tomorrow->y_axis[i]);
        for(j = 0; j < DAY_HOURS; j++)
        {
            printf(" %c ", tomorrow->graph.buffer[j][i]);
        }
        printf("\n");
    }
    printf("     ╰────────────────────────────────────────────────────────────────────────");
    printf("              ╰────────────────────────────────────────────────────────────────────────\n");
    printf("       00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23  %s", hour);
    printf("          00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23  %s\n\n", hour);
}

/* Responsible for printing each of the three tables. */
void print_tables(Tables* prices, Tables* co2)
{
    print_table(&prices->average, &co2->average);
    print_table(&prices->highest, &co2->highest);
    print_table(&prices->compare, &co2->compare);
}

/* Handles the printing of the input tables. */
void print_table(Strings* table_1, Strings* table_2){
    int i;

    int longest_table = table_1->index > table_2->index ? 
        table_1->index : table_2->index;

    for(i = 0; i < longest_table; i++){
        if(table_1->index > i){
            printf("%19s%s%24s", "", table_1->buffer[i], "");
        }
        if(table_1->index == longest_table && table_2->index <= i){
            printf("\n");
        }

        if(table_2->index > i && table_1->index > i){
            printf("%16s%s\n", "", table_2->buffer[i]);
        } else if (table_2->index == longest_table){
            printf("%106s%s\n", "", table_2->buffer[i]);
        }
    }
}

/* Used to complare floats and navigate around the small decimal issues we
   ran into along the way. Returns whether the first float is smaller (<0),
   equal (0) or bigger (>0) than the second float. */
/* https://www.geeksforgeeks.org/rounding-floating-point-number-two-decimal-places-c-c/ */
int compare_floats(float f1, float f2)
{
    float epsilon = 0.001f;

    f1 = (float)((int)(f1 * 100 + 0.5)) / 100;
    f2 = (float)((int)(f2 * 100 + 0.5)) / 100;

    return fabs(f1 - f2) < epsilon;
}

/* Used to compare integers. Returns whether the first integer is smaller (<0),
   equal (0) or bigger (>0) than the second int. */
int compare_intergers(const void* int1, const void* int2)
{
    return *((int*)int1)-*((int*)int2);
}

/* Returns whether the graph is relatively stable for the day. */
int less_than_step(float values[], float average)
{   
    Graph graph = {0};
    float min_y = 0, max_y = 0;

    find_extremes(values, &graph);

    max_y = ((double)((int)((graph.max_value + 0.5) * 2))) / 2;
    min_y = ((double)((int)(graph.min_value * 2))) / 2;
    graph.step = (max_y - min_y) / Y_AXIS_LENGTH;

    if(graph.step < 0.05)
    {
        graph.step = 0.05;
    }

    return ((graph.max_value - average) < graph.step);
}

/* Responsiible for dynamically fitting the table width. */
int* fill_table_width(char* string){
    int width1;
    int width2;
    int length = utf8_length(string);
    int* result = malloc(sizeof(int) * 2);
    int total_length = 0;

    width1 = ((TABLE_INNER_SIZE-length)/2);
    width2 = width1;
    total_length = width1 + width2 + length;

    if(total_length < TABLE_INNER_SIZE){
        width2 += TABLE_INNER_SIZE - total_length;
    }
    if(total_length > TABLE_INNER_SIZE){
        width2 -= TABLE_INNER_SIZE - total_length;
    }
    result[0] = width1;
    result[1] = width2;
    return result;
}

/* https://www.drk.com.ar/code/count-characters-in-utf8-string-c-utf8len.php */
/* This fixes a counting issue we had with UTF-8 characters, i.e. æ, ø and å. */
size_t utf8_length(const char *string)
{
    size_t length = 0;
    /* 
        We use the & operator it works by going through each bit of the character
        and checking if it existis in both *(strings) AND 0xC0.
        Example 'ø':
            'ø' is made of two parts the byte 0xC3 and the byte 0xB8
            C3: 11100101 B8: 10111000 
            C0: 11000000 C0: 11000000
                --------     --------
            C0: 11000000 80: 1000000
        this makes it so we only count 'ø' as a single character because we
        ignore 0xB8. UTF-8 chars can be up to 4 bytes long but in any case we
        only count the first character as we see in the example above.
    */
    while(*string)
        length += (*(string++)&0xC0)!=0x80;
    return length;
}
