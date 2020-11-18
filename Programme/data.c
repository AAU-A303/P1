/*
 ===============================================================================
 * File: data.c             Date completed: 16th of November, 2020
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
 * Description: This file manages our data, and is responsible for returning any
 *              data structs.
 ===============================================================================
 */

#include "energy.h"
#define TRUE 1
#define FALSE 0

typedef struct {
    int day;
    int month;
    int year;
} Date;

typedef struct {
    Date date;
    float prices[24];
} Energy_price;

Energy_price* get_data(char filepath[], int *energy_price_index);
void set_date(Date *date, char date_string[]);
int compare_dates(Date *date_a, Date *date_b);
int count_lines(char filepath[]);
Date initialize_date(void);

void print_date(Date date);
void print_energy_price(Energy_price energy_price);
void print_energy_price_array(Energy_price energy_price_array[], int length);

int main(void) {
    /* program starts here */
    int energy_price_length = 0;
    Energy_price* energy_price_array;
    /*
        We call the function get_data with the file path "./dataset/prices_2020_hourly_dkk.txt".
        And with the pointer to "energy_price_index", this ensures we know how many elements the
        "energy_price_array" contains.
    */
    energy_price_array = get_data("./dataset/prices_2020_hourly_dkk.txt", &energy_price_length);
    /*
        Here we call the print function that prints out the elements of the entire array.
    */
    print_energy_price_array(energy_price_array, energy_price_length);

    return EXIT_SUCCESS;
}

Energy_price* get_data(char filepath[], int *energy_price_index) {
    float price;
    char date_string[64];
    char line[128];
    int line_count, price_index = 0;
    Date date;
    Energy_price energy_price;
    Energy_price* energy_price_array;
    FILE* file;
    /*
        This function opens the "file" in read-only mode and increments every time it encounters a new line.
    */
    line_count = count_lines(filepath);
    /*
        We know the average length of a day so, we can calculate the number of days we need to store in the array.
    */
    energy_price_array = (Energy_price*)malloc(((line_count/24)+2) * sizeof(Energy_price));

    /*
        Check if the array was allocated correctly.
    */
    if(energy_price_array == NULL){
        printf("Was unable to allocate energy_prices array!\n");
    }
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
            Reset the initial energy_prices struct by setting it to date of "0/0/0".
            We do this to prevent the wrong dates from being loaded into the structure.
        */
        energy_price.date = (Date){0, 0, 0};
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
            set_date(&date, date_string);
            
            /*
                We compare the dates if the second date is larger than the first date.
                Then we have a new date, and we increment the "energy_price_index" and reset the "price_index".
                Then we add the "energy_price" to the "energy_price_array" at the "energy_price_index".
                The last thing we do is update the "energy_price" struct "date" field to the new date value.
            */
            if(compare_dates(&energy_price.date, &date)){
                *energy_price_index += 1;
                price_index = 0;
                energy_price_array[*energy_price_index] = energy_price;
                set_date(&energy_price.date, date_string);
                /* 
                    Maybe we should reset the "energy_price" prices fields in the case there's
                    less than 24 data points in a given date.
                */
            }
            /*
                For each loop, we add the current energy price to the "energy_price" "prices" field.
                And then increment the "price_index".
            */
            energy_price.prices[price_index] = price;
            price_index++;
        }
        /*
            After reading the last line, we exit. That means we won't append the last "energy_price" struct.
            We fix this by incrementing "energy_price_index" and appending the last "energy_price" struct.
        */
        *energy_price_index += 1;
        energy_price_array[*energy_price_index] = energy_price;

    } else {
        printf("Failed to open file \"%s\"\n\n", filepath);
    }
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

int count_lines(char filepath[]){
    FILE *file = fopen(filepath, "r");
    int current_char = 0, lines = 1;

    if (file != NULL){
        while((current_char = fgetc(file)) != EOF){
            if (current_char == '\n'){
                lines++;
            }
        }
    } else {
        printf("Failed to open file \"%s\"\n\n", filepath);
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