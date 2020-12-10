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
#if defined(_WIN32)
    #include<windows.h>
    #define SET_CONSOLE() SetConsoleOutputCP(65001)
#else
    #define SET_CONSOLE()
#endif

int main(void)
{
    User_data data = { 0 };
    SET_CONSOLE();
    system("cls || clear");
    print_string_from_id(data.language, "Welcome", 1);
    
    do {
        system("cls || clear");
        setup(&data);
    } while (has_new_inquiry(data));
    
    print_string_from_id(data.language, "Goodbye", 1);

    return EXIT_SUCCESS;
}
