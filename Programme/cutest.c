#include "./H_files/cutest.h"

void all_tests();
CuSuite* test_suite();
void test_load_data(CuTest* testContext);
void test_convert_kwh(CuTest* testContext);
void test_add_fees(CuTest* testContext);
void test_add_vat(CuTest* testContext);
void test_do_calculations(CuTest* testContext);
void test_get_localisation_indexes(CuTest* testContext);

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
        CuAssertFlEquals(testContext, temp, correct_array[i], 0.0001);
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
        CuAssertFlEquals(testContext, temp, correct_array[i], 0.0001);
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
        CuAssertFlEquals(testContext, temp, correct_array[i], 0.0001);
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
        CuAssertFlEquals(testContext, userdata.today.prices[i], correct_array_today[i],0.0001);
        CuAssertFlEquals(testContext, userdata.tomorrow.prices[i], correct_array_tomorrow[i],0.0001);
    }
}

void test_get_localisation_indexes(CuTest* testContext){
    int i, j;
    char input[7][256] = {
        "Welcome;Welcome to our prototype!;Velkommen til vores prototype!;Bienvenue dans notre prototype!;Tervetuloa prototyyppiin!;",
        "Supported_languages;Supported languages: ;Tilgængelige sprog: ;Langues prises en charge: ;Tuetut kielet: ;",
        "Select_language;Please select a language> ;Vælg et sprog> ;Veuillez sélectionner une langue> ;Valitse kieli> ;",
        "Continue;Would you like to check another day? Enter Y or N> ;Vil du teste en anden dag? Tast Y for ja og N for nej> ;Souhaitez-vous vérifier un autre jour? Entrez Y ou N> ;Haluatko tarkistaa toisen päivän? Syötä Y tai N> ;",
        "Select_date;Please enter the current date (DD/MM format)> ;Indtast den nuværende dato (DD/MM format)> ;Veuillez saisir la date actuelle (format JJ / MM)> ;Anna nykyinen päivämäärä (PP / KK-muoto)> ;",
        "Select_hour;Please enter the current hour (HH format)> ;Indtast den nuværende time (TT format)> ;Veuillez saisir l'heure actuelle (format HH)> ;Anna nykyinen tunti (HH-muoto)> ;",
        "Goodbye;Thank you for trying out our prototype!;Tak fordi du tog dig tid til at teste vores prototype!;Merci d'avoir essayé notre prototype!;Kiitos kokeilemisesta!;",
    };
    int correct_array[7][5] = {
        {7, 33, 64, 96, 122},
        {19, 41, 63, 90, 106},
        {15, 42, 59, 95, 111},
        {8, 60, 116, 172, 226},
        {11, 58, 103, 155, 203},
        {11, 55, 97, 144, 177},
        {7, 47, 102, 141, 164},
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
        for(j = 0; j < 5; j++){
            CuAssertIntEquals(testContext,correct_array[i][j], temp[i][j]);
        }
    }
}
