#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

float temperature = 76;
float turbidity = 67;

// defining colors for better console UI
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

// function to calculates a water-quality index
float water_quality(void) {
    float temperatureDeviation = fabsf(temperature - 25.0f);
    float turbidityPenalty = turbidity/2.0f;

    float index = 100 - (temperatureDeviation + turbidityPenalty);
    return index;
}

// function to print sensor results
void print_report(float index) {
    printf(BLUE "\n\n========= WATER SENSOR MONITORING REPORT============\n" RESET);
    printf("\tTemperature: %.1f C\n", temperature);
    printf("\tTurbidity: %.1f NTU\n", turbidity);
    printf("\tWater Quality Index: %.1f \n", index);

    if (index >= 80) {
        printf("\nWater Quality Status: ");
        printf(GREEN "GOOD\n" RESET);
    }

    else if (index >= 60 && index < 80) {
        printf("\nWater Quality Status: ");
        printf(YELLOW "WARNING!\n" RESET);
    }

    else {
        printf("\nWater Quality Status: ");
        printf(RED "CRITICAL\n" RESET);
    }
}

// Main function
int main(void) {
    srand(time(NULL));

    // loop to keep giving random numbers to the sensors mimicking a live sensor
    for (int reading = 1; reading <= 10; reading++)
    {
        temperature = rand() % 80; // 0-79 random values assigned
        turbidity = rand() % 100; // 0-99 random values assigned

        float index = water_quality();
        print_report(index);

        sleep(2);
    }

    return 0;
}

