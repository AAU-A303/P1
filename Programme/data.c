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
    float prices[HOURS_IN_DAY];
} Energy_price;

Energy_price* get_data(char filename[], int *energy_price_index);
void set_date(Date *date, char date_string[]);
int compare_dates(Date *date_a, Date *date_b);
int count_lines(char filename[]);
Date initialize_date(void);

void print_date(Date date);
void print_energy_price(Energy_price energy_price);
void print_energy_price_array(Energy_price energy_price_array[], int length);

int main(void) {
    /* program starts here */
    int energy_price_length = 0;
    Energy_price* energy_price_array;
    energy_price_array = get_data("./dataset/prices_2020_hourly_dkk.txt", &energy_price_length);
    print_energy_price_array(energy_price_array, energy_price_length);
    return EXIT_SUCCESS;
}
/* Add input parameter*/
Energy_price* get_data(char filename[], int *energy_price_index) {
    float price;
    char date_string[64];
    char line[128];
    int line_count, price_index = 0;
    Date date;
    Energy_price energy_price;
    Energy_price* energy_price_array;
    FILE* file;

    line_count = count_lines(filename);
    /**/
    energy_price_array = (Energy_price*)malloc(((line_count/24)+2) * sizeof(Energy_price));

    if(energy_price_array == NULL){
        printf("Was unable to allocate energy_prices array!\n");
    }
    
    file = fopen(filename, "r");

    if(file != NULL){
        energy_price.date.day = 0;
        energy_price.date.month = 0;
        energy_price.date.year = 0;
        while (fgets(line, sizeof(line), file)) {
            sscanf(line, "%s %f", date_string, &price);
            set_date(&date, date_string);

            if(compare_dates(&energy_price.date, &date)){
                *energy_price_index += 1;
                printf("Index: %d\n",*energy_price_index);
                price_index = 0;
                energy_price_array[*energy_price_index] = energy_price;
                set_date(&energy_price.date, date_string);
            }
            energy_price.prices[price_index] = price;
            price_index++;
        }
        *energy_price_index += 1;
        energy_price_array[*energy_price_index] = energy_price;

    } else {
        printf("Failed to open file \"%s\"\n\n", filename);
    }
    fclose(file);
    return energy_price_array;
}

void set_date(Date *date, char date_string[]){
    sscanf(date_string, "%d/%d/%d", &date->day, &date->month, &date->year);
}

int compare_dates(Date *date_a, Date *date_b){
    if(date_b->year > date_a->year){
        return TRUE;
    } else if (date_b->year == date_a->year){
        if(date_b->month > date_a->month){
            return TRUE;
        } else if (date_b->month == date_a->month) {
            if(date_b->day > date_a->day){
                return TRUE;
            } else if(date_b->day == date_a->day){
                return FALSE;
            }
        } else{
            return FALSE;
        }
    } else {
        return FALSE;
    }
}

int count_lines(char filename[]){
    FILE *file = fopen(filename, "r");
    int current_char = 0, lines = 1;

    if (file != NULL){
        while((current_char = fgetc(file)) != EOF){
            if (current_char == '\n'){
                lines++;
            }
        }
    } else {
        printf("Failed to open file \"%s\"\n\n", filename);
        return 0;
    }
    fclose(file);
    return lines;
}

void print_date(Date date){
    printf("%d/%d/%d ", date.day, date.month, date.year);
}

void print_energy_price_array(Energy_price energy_price_array[], int energy_price_length){
    int i = 0;
    printf("Array_length: %d\n", energy_price_length);
    for(i = 0; i <= energy_price_length; i++){
        print_energy_price(energy_price_array[i]);
    }
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
