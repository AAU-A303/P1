#include "./H_files/cutest.h"

int main(void)
{
  all_tests();
  return 0;
}

void all_tests() {
	CuString *output = CuStringNew();
	CuSuite *suite = CuSuiteNew();

	CuSuiteAddSuite(suite, test_suite());

	CuSuiteRun(suite);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
}

CuSuite* test_suite() {
  CuSuite* suite = CuSuiteNew();
  SUITE_ADD_TEST(suite, test_load_data);
  SUITE_ADD_TEST(suite, test_convert_kwh);
  SUITE_ADD_TEST(suite, test_add_fees);
  SUITE_ADD_TEST(suite, test_add_vat);
  SUITE_ADD_TEST(suite, test_do_calculations);
  SUITE_ADD_TEST(suite, test_get_localisation_indexes);
  SUITE_ADD_TEST(suite, test_get_string_from_id);
  SUITE_ADD_TEST(suite, test_utf8_length);
  SUITE_ADD_TEST(suite, test_fill_table_width);
  SUITE_ADD_TEST(suite, test_average_price);
  SUITE_ADD_TEST(suite, test_find_extremes);
  return suite;
}

void test_load_data(CuTest* testContext){
    int i;
    User_data userdata = {0};
    Date date = {0};

    /* first array is price data, second array is co2 emission data. */
    float correct_array[4][24] = {
        {
            215.42,185.31,184.79,180.83,180.83,183.37,260.78,304.42,327.88,
            299.78,282.52,237.02,193.6,189.64,188.15,184.64,243.97,276.1,
            284.24,257.72,202.5,197.34,182.62,165.88
        },{
            122.1666667,106.3333333,103.25,105,105.3333333,112.5833333,
            108.3333333,99.41666667,98.25,97.16666667,96,99.83333333,
            90.91666667,92.75,95,96.41666667,101.25,94.91666667,88.83333333,
            91.08333333,85,78,72.33333333,84.91666667,
        },{
            2.99,23.24,70.39,70.91,70.17,64.79,76.07,86.38,97.07,104.69,92.36,
            74.5,50.14,69.12,69.34,69.64,39.01,91.54,104.02,95.5,60.23,55.15,
            77.79,71.06
        },{
            87.16666667,80.33333333,78.66666667,77.16666667,76.25,73.75,
            73.08333333,72.5,70.16666667,66.5,67.08333333,65.83333333,
            64.83333333,63.83333333,64.58333333,66.16666667,75.83333333,87.25,
            94.75,92.91666667,96.66666667,110.0833333,105.9166667,102.1666667
        }
    };

    /* Sample date */
    date.day = 28;
    date.month = 2;
    date.year = 2020;
    
    get_data(&userdata, date);

    for(i = 0; i < 24; i++){
        CuAssertFlEquals(testContext, correct_array[0][i], (userdata.today.prices[i]), 0);
    }
    for(i = 0; i < 24; i++){
        CuAssertFlEquals(testContext, correct_array[1][i], (userdata.today.co2_emissions[i]), 0);
    }
    for(i = 0; i < 24; i++){
        CuAssertFlEquals(testContext, correct_array[2][i], (userdata.tomorrow.prices[i]), 0);
    }
    for(i = 0; i < 24; i++){
        CuAssertFlEquals(testContext, correct_array[3][i], (userdata.tomorrow.co2_emissions[i]), 0);
    }
}

void test_convert_kwh(CuTest* testContext){
    int i;
    float temp;
    
    float input_array[24] = {
        72.07,96.87,137.20,18.63,26.17,105.71,149.70,63.12,167.70,104.24,83.88,
        109.40,55.19,104.44,43.46,109.27,195.90,101.46,69.91,146.14,172.94,
        161.67,108.67,113.68
    };

    float correct_array[24] = {
        0.07207,0.09687,0.1372,0.01863,0.02617,0.10571,0.1497, 
        0.06312,0.1677,0.10424,0.08388,0.1094,
        0.05519, 0.10444, 0.04346, 0.10927,
        0.1959,0.10146,0.06991,0.14614,0.17294,
        0.16167,0.10867,0.11368
    };

    for(i = 0; i < 24; i++){
        temp = input_array[i];
        convert_kwh(&temp);
        CuAssertFlEquals(testContext, correct_array[i], temp, 0.0001);
    }

}

void test_add_fees(CuTest* testContext){
    int i;
    float temp;

    float input_array[24] = {
        0.07207,0.09687,0.1372,0.01863,0.02617,0.10571,0.1497,0.06312,0.1677,
        0.10424,0.08388,0.1094,0.05519,0.10444,0.04346,0.10927,0.1959,0.10146,
        0.06991,0.14614,0.17294,0.16167,0.10867,0.11368
    };

    float correct_array[24] = {
        1.68207,1.70687,1.7472,1.62863,1.63617,1.71571,1.7597,1.67312,1.7777,
        1.71424,1.69388,1.7194,1.66519,1.71444,1.65346,1.71927,1.8059,1.71146,
        1.67991,1.75614,1.78294,1.77167,1.71867,1.72368
    };

    for(i = 0; i < 24; i++){
        temp = input_array[i];
        add_fees(&temp);
        CuAssertFlEquals(testContext, correct_array[i], temp, 0.0001);
    }
}

void test_add_vat(CuTest* testContext){
    int i;
    float temp;

    float input_array[24] = {
        1.68207,1.70687,1.7472,1.62863,1.63617,1.71571,1.7597,1.67312,1.7777,
        1.71424,1.69388,1.7194,1.66519,1.71444,1.65346,1.71927,1.8059,1.71146,
        1.67991,1.75614,1.78294,1.77167,1.71867,1.72368
    };

    float correct_array[24] = {
        2.1025875,2.1335875,2.184,2.0357875,2.0452125,2.1446375,2.199625,
        2.0914,2.222125,2.1428,2.11735,2.14925,2.0814875,2.14305,2.066825,
        2.1490875,2.257375,2.139325,2.0998875,2.195175,2.228675,2.2145875,
        2.1483375,2.1546
    };

    for(i = 0; i < 24; i++){
        temp = input_array[i];
        add_vat(&temp);
        CuAssertFlEquals(testContext, correct_array[i], temp, 0.0001);
    }
}

void test_do_calculations(CuTest* testContext){
    int i;

    float correct_array_today[24] = {
        2.281775,2.2441375,2.2434875,2.2385375,2.2385375,2.2417125,2.338475,
        2.393025,2.42235,2.387225,2.36565,2.308775,2.2545,2.24955,2.2476875,
        2.2433,2.3174625,2.357625,2.3678,2.33465,2.265625,2.259175,2.240775,
        2.21985
    };

    float correct_array_tomorrow[24] = {
        2.0162375,2.04155,2.1004875,2.1011375,2.1002125,2.0934875,2.1075875,
        2.120475,2.1338375,2.1433625,2.12795,2.105625,2.075175,2.0989,2.099175,
        2.09955,2.0612625,2.126925,2.142525,2.131875,2.0877875,2.0814375,
        2.1097375,2.101325
    };

    float today_prices[24] = {
        215.42,185.31,184.79,180.83,180.83,183.37,260.78,304.42,327.88,
        299.78,282.52,237.02,193.6,189.64,188.15,184.64,243.97,276.1,
        284.24,257.72,202.5,197.34,182.62,165.88
    };

    float tomorrow_prices[24] = {
        2.99,23.24,70.39,70.91,70.17,64.79,76.07,86.38,97.07,104.69,92.36,74.5,
        50.14,69.12,69.34,69.64,39.01,91.54,104.02,95.5,60.23,55.15,77.79,71.06
    };

    User_data userdata = {0};

    /* Coresponding data */
    for(i = 0; i < 24; i++){
        userdata.today.prices[i] = today_prices[i];
        userdata.tomorrow.prices[i] = tomorrow_prices[i];
    }

    do_calculations(&userdata);

    for(i = 0; i < 24; i++){
        CuAssertFlEquals(testContext, correct_array_today[i], userdata.today.prices[i], 0.0001);
        CuAssertFlEquals(testContext, correct_array_tomorrow[i], userdata.tomorrow.prices[i], 0.0001);
    }
}

void test_get_localisation_indexes(CuTest* testContext){
    int i, j;

    char input[7][256] = {
        "Welcome;Welcome to our prototype!;Velkommen til vores prototype!;",
        "Supported_languages;Supported languages: ;Tilgængelige sprog: ;",
        "Select_language;Please select a language> ;Vælg et sprog> ;",
        "Continue;Would you like to check another day? Enter Y or N> ;Vil du teste en anden dag? Tast Y for ja og N for nej> ;",
        "Select_date;Please enter the current date (DD/MM format)> ;Indtast den nuværende dato (DD/MM format)> ;",
        "Select_hour;Please enter the current hour (HH format)> ;Indtast den nuværende time (TT format)> ;",
        "Goodbye;Thank you for trying out our prototype!;Tak fordi du tog dig tid til at teste vores prototype!;",
    };

    int correct_array[7][3] = {
        {7, 33, 64},
        {19, 41, 63},
        {15, 42, 59},
        {8, 60, 116},
        {11, 58, 103},
        {11, 55, 97},
        {7, 47, 102},
    };

    int temp[7][5];

    get_localisation_indexes(temp[0], input[0]);
    get_localisation_indexes(temp[1], input[1]);
    get_localisation_indexes(temp[2], input[2]);
    get_localisation_indexes(temp[3], input[3]);
    get_localisation_indexes(temp[4], input[4]);
    get_localisation_indexes(temp[5], input[5]);
    get_localisation_indexes(temp[6], input[6]);

    for(i = 0; i < 7; i++){
        for(j = 0; j < 3; j++){
            CuAssertIntEquals(testContext, correct_array[i][j], temp[i][j]);
        }
    }
}

void test_get_string_from_id(CuTest* testContext){
    int i, j;
    char correct_array[46][256] = {
        "Welcome to our prototype!",
        "Supported languages: ",
        "Please select a language> ",
        "Try again! Please choose one of the above listed numbers",
        "Please enter the current date (DD/MM format)> ",
        "Try again! Please use the format as shown above and only numbers",
        "Please enter the current hour (HH format)> ",
        "ENERGY PRICES ",
        "The cheapest prices of the day",
        "The most expensive prices of the day",
        "Today, the prices are relatively stable",
        "Tomorrow's prices are %3.1f%% more expensive",
        "Tomorrow's prices are %3.1f%% cheaper",
        "CARBON EMISSIONS ",
        "The most environmental hours",
        "The least eco friendly hours",
        "Today, the emissions are relatively stable",
        "Tomorrow's emissions are %3.1f%% higher",
        "Tomorrow's emissions are %3.1f%% lower",
        "HOUR",
        "Would you like to see the data for tomorrow? Enter Y or N> ",
        "Would you like to check another day? Enter Y or N> ",
        "Thank you for trying out our prototype!",
        "Velkommen til vores prototype!",
        "Tilgængelige sprog: ",
        "Vælg et sprog> ",
        "Prøv igen! Vær venlig at bruge en af de listede tal ovenfor",
        "Indtast den nuværende dato (DD/MM format)> ",
        "Prøv igen! Brug formatet som er vist ovenfor og brug kun tal",
        "Indtast den nuværende time (TT format)> ",
        " ENERGIPRISER ",
        "Dagens billigste tidspunkter",
        "Dagens dyreste tidspunkter",
        "I dag er priserne relativt stabile",
        "Priserne for i morgen er %3.1f%% dyrere",
        "Priserne for i morgen er %3.1f%% billigere",
        " CO2 UDSLIP ",
        " Dagens mest miljøvenlige tider ",
        " Dagens mindst miljørigtige tider ",
        "I dag er CO2 udslippet relativt stabilt",
        "Udslippet for i morgen er %3.1f%% højere",
        "Udslippet for i morgen er %3.1f%% lavere",
        "TIME",
        "Vil du se datasættet for i morgen også? Tast Y for ja og N for nej> ",
        "Vil du teste endnu en dag? Tast Y for ja og N for nej> ",
        "Tak fordi du tog dig tid til at teste vores prototype!"
    };
    char input_array[23][256] = {
        "Welcome",
        "Supported_languages",
        "Select_language",
        "Fail_message_language",
        "Select_date",
        "Fail_message_general",
        "Select_hour",
        "Graph_price",
        "Table_prices_low",
        "Table_prices_high",
        "Table_prices_neutral",
        "Price_compare_positive",
        "Price_compare_negative",
        "Graph_CO2",
        "Table_CO2_low",
        "Table_CO2_high",
        "Table_CO2_neutral",
        "CO2_compare_positive",
        "CO2_compare_negative",
        "Time",
        "Tomorrow",
        "Continue",
        "Goodbye"
    };

    for(i = 0; i < 2; i++){
        for(j = 0; j < 23; j++){
            CuAssertStrEquals(testContext, correct_array[j + (23*i)], get_string_from_id(i, input_array[j]));
        }
    }
    
}

void test_utf8_length(CuTest* testContext){
    int i;
    char input_array[7][256] = {
        "hællo",
        "æøå",
        "æøåÆØÅ",
        "╰─────────────────────────────────────────────╯",
        "│%*s%s%*s│",
        "│            %02d:00 ─> %3.2f %*s            │",
        "?*^å"
    };
    int correct_array[7] = {
        5,3,6,47,10,46,4
    };
    for(i = 0; i < 7; i++){
        CuAssertIntEquals(testContext, correct_array[i], utf8_length(input_array[i]));
    }
}

void test_fill_table_width(CuTest* testContext){
    int i;
    int *temp;
    char input_array[7][256] = {
        "hællo",
        "æøå",
        "æøåÆØÅ",
        "─────────────────────────────────────────────",
        "│%*s%s%*s│",
        "%02d:00 ─> %3.2f %*s",
        "?*^å"
    };

    int correct_array[7][2] = {
        {20,20},
        {21,21},
        {19,20},
        {0,0},
        {17,18},
        {12,13},
        {20,21}
    };

    for(i = 0; i < 7; i++){
        temp = fill_table_width(input_array[i]);
        CuAssertIntEquals(testContext, correct_array[i][0], temp[0]);
        CuAssertIntEquals(testContext, correct_array[i][1], temp[1]);
    }
}

void test_average_price(CuTest* testContext){
    int i;
    float input_array[5][24] = {
        {
            138.2,142.01,74.27,181.57,52.08,112.3,92.18,101.87,27.75,95.02,
            86.57,116.32,44.1,179.82,67.54,166.45,97.88,129.38,171.45,29.83,
            187.23,140.17,4.79,16.29
        },
        {
            148.55,12.44,181.59,54.29,132.29,94.36,94.16,164.48,150.65,108.99,
            181.85,12.55,178.89,66.94,83.64,50.35,120.09,63.68,121.85,154.92,
            98.16,35.49,120.08,40.46
        },
        {
            96.51,128.45,134.56,50.96,156.5,74.14,196.57,85.8,134.93,75.61,
            106.58,77.26,37.55,61.85,56.79,119.87,96.19,149.84,193.23,65.18,
            180.8,199.58,95.9,190.34
        },
        {
            96.55,163.37,71.5,104.67,123.62,97.02,75.03,182.14,94.81,87,196.65,
            92.33,176.8,103.36,26.22,111.28,101.17,43.84,111.17,103.9,97.8,
            94.06,70.5,49.31
        },
        {
            195.72,51.64,61.73,47.38,117.32,132.9,90.54,84.54,84.53,194.58,
            158.32,136.59,156.03,168.05,72.46,103.77,157.93,126.75,17.45,118.11,
            47.28,41.21,140.73,102.49
        }
    };

    float correct_array[5] = {
        102.29458,
        102.94792,
        115.20792,
        103.0875,
        108.66875
    };

    for(i = 0; i < 5; i++){
        CuAssertFlEquals(testContext, correct_array[i], average_value(input_array[i]), 0.001);
    }
}

void test_find_extremes(CuTest* testContext){
    int i = 0;
    Graph temp;
    float input_array[5][24] = {
        {
            98.38,1.72,97.61,83.31,91.06,176.49,199.97,102.19,52.71,98.51,
            116.19,132.45,38.95,74.36,78.64,83.07,171.35,131.13,164.71,104.18,
            29.35,134.97,155.92,117.94
        },
        {
            80.99,107.15,195.5,143.21,92.24,77.31,106.26,29.85,144.18,89.76,
            99.72,100.33,62.8,106.7,156.46,93.32,111,88.11,195.14,83.26,173.31,
            176.05,124.71,102.42
        },
        {
            198.84,159.59,153.63,190.28,162.35,17.43,28.52,110.68,84.55,154.59,
            166.23,83.01,81.73,170.18,195.82,127.26,81.47,182.39,36.57,135.45,
            55.95,176.54,162.1,55.37
        },
        {
            54.1,98.72,178.03,96.66,117.09,103.47,79.69,10.22,74,124.18,121.69,
            21.7,26.14,99.67,103.43,60.65,64.75,94.37,135.43,36.97,42.56,91.25,
            113.81,125.08
        },
        {
            77.33,1.7,194.02,49.67,62.75,117.97,61.09,184.56,79.04,115.4,45.59,
            88.51,88.92,83.76,106.11,99.48,114.41,192.79,198.41,85.72,141.77,
            31.15,45.35,13.2
        }
    };
    float correct_array[5][2] = {
        {199.97, 1.72},
        {195.5,29.85},
        {198.84, 17.43},
        {178.03, 10.22},
        {198.41, 1.7}
    };
    for(i = 0; i < 5; i++){
        find_extremes(input_array[i], &temp);
        CuAssertFlEquals(testContext,correct_array[i][0], temp.max_value, 0.001);
        CuAssertFlEquals(testContext,correct_array[i][1], temp.min_value, 0.001);
    }
}