#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

// defining colors for better console UI
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define RESET   "\033[0m"

// global variables
char username[] = "Thadee Gatete";
double acc_balance = 0;

#define MAX_TRANSACTIONS 100
#define DATE_TIME_LENGTH 20

// defining transaction type and its identification number
#define DEPOSIT 1
#define WITHDRAWAL 2

// declaring the transactions summary arrays
int transaction_types[MAX_TRANSACTIONS];
double transaction_amounts[MAX_TRANSACTIONS];
char transaction_dates[MAX_TRANSACTIONS][DATE_TIME_LENGTH];

// transactions counting variables
int transaction_count = 0;
int deposit_count = 0;
int withdrawal_count = 0;

// function prototypes to allow any order of declaration
void menu(void);
void deposit(void);
bool ask_restart_transaction(void);
void save_transaction(int type, double amount);
void print_transactions_summary(void);
void check_account_balance(void);
void withdraw(void);
double process_transaction(char type[], int limit);

// creating a function to clear console contents
void clear_console(void)
{
    printf("\033c");
    fflush(stdout);
}

// creating the function for menu selection
void menu(void) {
    bool running = true;

    while (running) {
        int choice = 0;
        int character;
        char next_character;

        printf(BLUE "\n\t===== MOBILE MONEY TRANSACTION SYSTEM =====" RESET);
        printf("\n\t1. Deposit");
        printf("\n\t2. Withdraw");
        printf("\n\t3. Check Balance");
        printf("\n\t4. Transaction Summary");
        printf("\n\t5. Exit");
        printf(YELLOW "\n\t Note: Choose a valid number from 1-4 or 5 to Exit " RESET);

        printf("\n\n Choose an action to proceed: ");

        // checking if a non-numeric value is entered
        if (scanf("%d%c", &choice, &next_character) != 2 || next_character != '\n') {

            // removing  the non-numeric input
            while ((character = getchar()) != '\n' && character != EOF) {}
            choice = 0;
        }

        switch (choice) {
            case 1:
                printf(GREEN "\n\t Starting Deposit...\n" RESET);
                sleep(1);
                deposit();
                break;

            case 2:
                printf(GREEN "\n\t Starting Withdrawal...\n" RESET);
                sleep(1);
                withdraw();
                break;

            case 3:
                printf(GREEN "\n\t Checking Balance...\n" RESET);
                sleep(1);
                check_account_balance();
                break;

            case 4:
                printf(GREEN "\n\t Loading Your Transaction Summary...\n" RESET);
                sleep(1);
                clear_console();
                print_transactions_summary();
                break;

            case 5:
                running = false;
                printf(GREEN "\n\t Program Closed Successfully!\n" RESET);
                break;

            default:
                clear_console();
                printf(RED "\n\t Invalid Choice, please select a valid option\n" RESET);

                fflush(stdout);
                continue;
        }
    }
}

// asking the user if they want to exit after each transaction
bool ask_restart_transaction(void) {
    char choice[4];
    int character;
    printf("\n\t Press y/yes to restart");
    printf("\n\t Press any other character to go back to the main menu");
    printf(BLUE"\nDo you want to perform this transaction again? " RESET);
    scanf("%3s", choice);

    while ((character = getchar()) != '\n' && character != EOF){}

    if (strcmp(choice, "y") == 0 || strcmp(choice, "Y") == 0
        || strcmp(choice, "YES") == 0 || strcmp(choice, "yes") == 0) {
        return true;
    }

    clear_console();
    return false;

}

double process_transaction(char type[], int limit) {
    double amount;
    int character;
    char next_character;

    while (true) {
        clear_console();
        printf("\n\t====Welcome, %s!\n", username);
        printf("\nEnter the %s amount (at least %d RWF): ", type, limit);

        // checking if a non-numeric value is entered
        if (scanf("%lf%c", &amount, &next_character) != 2 || next_character != '\n') {

            // removing  the non-numeric input
            while ((character = getchar()) != '\n' && character != EOF) {}
            printf(RED "\nInvalid input, please enter a valid amount\n" RESET);
            if (ask_restart_transaction())
                continue;
            return (-1);
        }

        // checking if amount is a negative value or below 100
        else if (amount < limit) {
            printf(RED "\nInvalid %s amount, Must be at least %d RWF\n" RESET, type, limit);
            if (ask_restart_transaction())
                continue;
            return (-1);
        }
        return amount;

    }
}

void deposit(void) {
    while (true) {
        double amount = process_transaction("deposit", 100);

        // return if invalid amount
        if (amount == -1)
            return;
        save_transaction(DEPOSIT, amount);
        deposit_count++;
        acc_balance += amount;
        printf(GREEN "\nTransaction Successful! %.2f has been added to your account\n" RESET, amount);
        printf(BLUE "NEW BALANCE: %.2f\n" RESET, acc_balance);
        sleep(1);

        if (ask_restart_transaction())
            continue;
        return;
    }
}

void withdraw(void) {
    while (true) {
        double amount = process_transaction("withdrawal", 50);
        // return if invalid amount
        if (amount == -1)
            return;

        if (amount > acc_balance) {
            printf(RED"\n\n\tSorry, Insufficient Funds! You only have %.2f\n" RESET, acc_balance);
        }
        else {
            save_transaction(WITHDRAWAL, amount);
            withdrawal_count++;
            acc_balance -= amount;
            printf(YELLOW"\n\tWithdrawal Processing... Please take your cash! \n\n"RESET);
            sleep(2);
            printf(GREEN "\nTransaction Successful! You have withdrawn %.2f RWF from your account\n" RESET, amount);
            printf(BLUE "NEW BALANCE: %.2f\n" RESET, acc_balance);
            sleep(1);
        }

        if (ask_restart_transaction())
            continue;
        return;
    }
}

// function to save each transaction in the arrays for transactions history
void save_transaction(int type, double amount)
{
    time_t current_time;
    struct tm *local_time;

    // maximum of 100 transactions allowed
    if (transaction_count >= MAX_TRANSACTIONS)
    {
        printf(RED "\nTransaction history is full.\n" RESET);
        return;
    }

    transaction_types[transaction_count] = type;
    transaction_amounts[transaction_count] = amount;

    current_time = time(NULL);
    local_time = localtime(&current_time);

    strftime(transaction_dates[transaction_count],
         DATE_TIME_LENGTH,
         "%d-%m-%Y %H:%M:%S",
         local_time);

    transaction_count++;
}

void check_account_balance(void) {
    clear_console();
    printf("\n\tHello, %s!", username);
    printf(BLUE "\n\t\t Your Account Balance is %.2f\n\n" RESET, acc_balance);
    sleep(2);
}

void print_transactions_summary(void) {

    if (transaction_count < 1) {
        printf(RED "\nNo Transactions Found! You have not made any transaction today.\n" RESET);
        return;
    }
    printf(BLUE "\n\t===========Transactions History===========" RESET);
    printf(BLUE"\n\tTotal Number of Transactions: %d\n" RESET, transaction_count);
    printf("Deposits (%d) | Withdrawals (%d)\n\n", deposit_count, withdrawal_count);
    for (int i = 0; i < transaction_count; i++)
    {
        if (transaction_types[i] == DEPOSIT)
        {
            printf("%d. Deposit", i + 1);
        }
        else
        {
            printf("%d. Withdrawal", i + 1);
        }

        printf(" | %.2f RWF | %s\n",
               transaction_amounts[i],
               transaction_dates[i]);
    }
    sleep(2);
}

int main(void) {
    menu();
    return 0;
}