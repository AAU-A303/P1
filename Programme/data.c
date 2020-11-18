/*
 ===============================================================================
 * File: data.c                     Date completed: 16th of November, 2020
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
 * Description: This file manages our data, and is responsible for returning any
 *              data structs.
 ===============================================================================
 */

#include "energy.h"

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    Date date;
    float prices[DAY_HOURS];
} Energy_price;

typedef struct {
    Energy_price today;
    Energy_price tomorrow;
    int access_tomorrow;
} Price_data;

Price_data get_data(char filepath[], Date target_date);
void date_set(Date *date, char date_string[]);
int date_equals(Date *date_a, Date *date_b);
int date_diffrence_in_days(Date *date_a, Date *date_b);

void print_date(Date date);
void print_energy_price(Energy_price energy_price);
void print_price_data(Price_data price_data);

int main(void) {
    /* program starts here */
    int energy_price_length = 0;
    Price_data price_data;
    Date today = (Date){5, 11, 2020};
    /*
        We call the function get_data with the file path "./dataset/prices_2020_hourly_dkk.txt".
        And with the pointer to "energy_price_index", this ensures we know how many elements the
        "energy_price_array" contains.
    */
    price_data = get_data("./dataset/prices_2020_hourly_dkk.txt", today);
    /*
        Here we call the print function that prints out the elements of the entire array.
    */
    print_price_data(price_data);

    return EXIT_SUCCESS;
}

Price_data get_data(char filepath[], Date target_date) {
    float price;
    char date_string[64];
    char line[128];
    int index_today = 0, index_tomorrow = 0;
    Date current_date = {0};
    Energy_price today = {0};
    Energy_price tomorrow = {0};
    Price_data price_data = {0};
    FILE* file;
    /*
        "fopen" opens a file given a "filepath" and the "mode" of which to open the file.
        In this case, we just need to read the file so we use the "r" mode.
        ("r" = read), ("w" = write), ("a" = append) and ("+" = update). These modes can be combined with each other.
    */
    file = fopen(filepath, "r");
    /*
        If the "file" is "NULL", then we were unable to either find or open the file.
    */
    if(file != NULL){
        /*
            While there's still a new line, fill the char array with its contents.
        */
        while (fgets(line, sizeof(line), file)) {
            /*
                split up the line into the format:
                char[]: "string_date" and float: "price"
            */
            sscanf(line, "%s %f", date_string, &price);
            /*
                split up the "date_string" int to the format:
                int: day
                int: month
                int: year
            */
            date_set(&current_date, date_string);
            /*
                First, we check if the "current_date" is equal to the "target_date".
                If the two dates are equal we set "today.date" to the current_date
                and we add the "current_price" to the "today.price" array at the "index_today".
                If the check fails we check if its the next day instead.
                And if it is the next day we set the "tomorrow.date" and "tomorrow.price" at "index_tomorrow".
            */
            if(date_equals(&current_date, &target_date)){
                date_set(&today.date, date_string);
                today.prices[index_today] = price;
                index_today++;
            } else {
                if(date_diffrence_in_days(&target_date, &current_date) == 1){
                    date_set(&tomorrow.date, date_string);
                    tomorrow.prices[index_tomorrow] = price;
                    index_tomorrow++;
                }
            }
        }
    } else {
        printf("Failed to open file \"%s\"\n\n", filepath);
    }
    /*
        Now that we have populated the "Energy_price" struct "today" and "tomorrow".
        we can add them to "price_data.today" and "price_data.tomorrow".
    */
    price_data.today = today;
    price_data.tomorrow = tomorrow;
    /*
        It's important to remember to close the file after opening it.
        The result of not closing the file is that both other programs and this program
        will be unable to open the file again until this program exits.
    */
    fclose(file);
    /*
        The last thing we do is return the output parameter "energy_price_index".
        And return the "energy_price_array" as a return value.
    */
    return price_data;
}

void date_set(Date *date, char date_string[]){
    sscanf(date_string, "%d/%d/%d", &date->day, &date->month, &date->year);
}

int date_diffrence_in_days(Date *date_a, Date *date_b){
    struct tm current_date = { 0 };
    struct tm next_date = { 0 };
    double current_date_seconds;
    double next_date_seconds;
    /*
        Add out date values to the tm struct.
        We subtract 1900 from the year since tm_year is specified by the years since 1900.
        We subtract 1 from the month since tm_month is int the range 0-11.  
    */
    current_date.tm_year = date_a->year - 1900;
    current_date.tm_mon = date_a->month - 1;
    current_date.tm_mday = date_a->day;

    next_date.tm_year = date_b->year - 1900;
    next_date.tm_mon = date_b->month - 1;
    next_date.tm_mday = date_b->day;

    current_date_seconds = mktime(&current_date);
    next_date_seconds = mktime(&next_date);

 
}

int date_equals(Date *date_a, Date *date_b){
    if(date_a->year == date_b->year){
        if(date_a->month == date_b->month){
            if(date_a->day == date_b->day){
                return TRUE;
            }
        }
    } return FALSE;
}

void print_date(Date date){
    printf("%d/%d/%d ", date.day, date.month, date.year);
}

void print_energy_price(Energy_price energy_price){
    int j = 0;
    printf("Date: ");
    print_date(energy_price.date);
    printf("\n");
    for(j = 0; j < 24; j++){
        printf("\tHour: %d Price: %.2f\n", j, energy_price.prices[j]);
    }
}

void print_price_data(Price_data price_data){
    print_energy_price(price_data.today);
    print_energy_price(price_data.tomorrow);
    printf("Access to tomorrow: %d \n",price_data.access_tomorrow);
}