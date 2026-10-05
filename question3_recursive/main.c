#include <stdbool.h>
#include <stdio.h>

int n = 0;
int limit = 0;

// Creating one function to validate all numbers input in the program
bool input_validation(int value, int scan_result, int next_character) {
    int character;

    if ((scan_result != 1) || (next_character != '\n')){
        if (next_character != '\n') {
            while ((character = getchar()) != '\n' &&
                   character != EOF){}
        }
        printf("\nError! Enter a valid number.\n\n");
        return false;
    }
    if (value < 1) {
        printf("\nError! Enter a number from 1 and above\n\n");
        return false;
    }
    return true;
}

// creating the function to ask user to enter both number of distance and limit.
void ask_route_and_limit(char message[50], bool route){
    bool valid_input = false;
    int value = 0;

    while (!valid_input) {
        printf("%s", message);
        int scan_result = scanf("%d", &value);
        int next_character = getchar();
        valid_input = input_validation(value,scan_result,next_character);
    }
    if (route) {
        n = value;
    }
    else {
        limit = value;
    }

}

// creating the function for accepting the deliver route numbers from the user
void add_delivery_routes(int distances[]) {
    bool valid_input;
    int value = 0;

    for (int i = 0; i < n; i++) {
        valid_input = false;

        // validating every input to prevent the distance array from breaking
        while (!valid_input) {
            value = 0;
            printf("\nEnter the Distance of Route No %d: ", i+1);
            int scan_result = scanf("%d", &value);

            int next_character = getchar();
            valid_input = input_validation(value,scan_result,next_character);
        }
        distances[i] = value;
    }
}

// calculating the total distance using a for loop
int total_distance(int distances[]) {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += distances[i];
    }
    return total;
}

// A recursive function to perform total using recursive instead of loop
int recursive_sum(int distances[], int size){
    if (size == 0){
        return 0;
    }
    return distances[size - 1] + recursive_sum(distances, size - 1);
}

// calculating the average distance
float average_distance(int total) {
    return (float)total / (float)n;
}

// calculating the number of distance values above the limit set by the user
int no_above_limit(int distances[]) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (distances[i] > limit) {
            count++;
        }
    }
    return count;
}

// returning the longest distance entered by the user
int longest_distance(int distances[]) {
    int longest = distances[0];
    for (int i = 1; i < n; i++) {
        if (distances[i] > longest) {
            longest = distances[i];
        }
    }
    return longest;
}

// Printing the analysis result and showing it on the console in a structured way.
void print_analysis(int total, float average, int longest, int above_limit, int sum, int distances[]) {
    printf("\n\n===== DELIVERY DISTANCE ANALYSIS =====\n");

    printf("Distances Given: [");
    for (int i = 0; i < n; i++) {
        printf("%d", distances[i]);
        if (i != n-1) {
            printf(", ");
        }
    }
    printf("]\n");

    printf("\n\t Total Distance: %dkm", total);
    printf("\n\t Recursive Sum of Distances: %dkm\n", sum);

    printf("\n\t Average Distance: %.2fkm", average);
    printf("\n\t Longest Distance: %dkm", longest);
    printf("\n\t Distances Above Set limit of %dkm: %d\n\n", limit, above_limit);
}

int main(void) {
    ask_route_and_limit("How many Routes do you want to add: ", true);
    int distances[n];

    add_delivery_routes(distances);

    ask_route_and_limit("Enter the Distance Limit: ", false);

    // Calling all calculation functions and pasisng the result to print analysis
    print_analysis(total_distance(distances),
        average_distance(
            total_distance(distances)
            ),
        longest_distance(distances),
        no_above_limit(distances),
        recursive_sum(distances, n),
        distances);

   return 0;
}

