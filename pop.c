/*  
2023-07-19
pop.c
Mahnaz Fayezi
Student ID:501212080 
Assignment #3 - Simulate Washing Machine
CPS 393 Section FB0
Instructor: Instructor: L. Hiraki
Purpose: To simulate operation of pop vending machine.

I certify that the program and code are my own work.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

// COIN1:NICKEL, COIN2:DIME, COIN3:PENTE
// its written this way for international use
#define COIN1 5
#define COIN2 10
#define COIN3 20
#define PRICE_MULT 5
#define MIN_PRICE 30
#define MAX_PRICE 105

void calculate_change(int change) {
    // converts the change int into dimes and nickles, and outputs it into the console
    // called every transaction end
    // EXPECTS: the amount of change remaining
    // RETURNS: nothing, just outputs the amount of change returned
    int num_dimes = change / COIN2;
    int num_nickels = (change % COIN2) / COIN1;
    printf("    Change given: %d centimes as %d dime(s) and %d nickel(s).\n", change, num_dimes, num_nickels);
}

int main(int argc, char *argv[]) {
    // error if price isn't given
    if (argc != 2) {
        printf("Please specify selling price as a command line argument.\nUsage: pop [price]\n");
        return 1;
    }

    // error if price isn't valid (within range)
    int price = atoi(argv[1]);
    if (price < MIN_PRICE || price > MAX_PRICE) {
        printf("Price must be from %d to %d centimes.\n", MIN_PRICE, MAX_PRICE);
        return 1;
    }
    
    // error if price isn't valid (multiple of 5 or what the engineer sets PRICE_MULT to)
    if (price % PRICE_MULT != 0) {
        printf("Price must be a multiple of %d.\n", PRICE_MULT);
        return 1;
    }

    int total_inserted;
    char coin;
    int change;
    // this flag bool is to break two levels of nested loops if its set to true
    // allows us to reset the machine after user cancels the transaction
    bool returning = false;
    printf("Welcome to my C Pop Machine!\n");

    while (1) {
        // reseting variables on each sell/return
        total_inserted = 0;
        change = 0;
        returning = false; 
        printf("Pop is %d centimes. Please insert any combination of nickels [N or n], dimes [D or d] or Pentes [P or p]. You can also press R or r for coin return.\n", price);

        while (total_inserted < price && !returning) {
            printf("Enter coin (NDPR): ");
            scanf(" %c", &coin);
            coin = toupper(coin);

            switch (coin) {
                case 'N':
                    total_inserted += COIN1;
                    printf("  Nickel detected.\n");
                    break;
                case 'D':
                    total_inserted += COIN2;
                    printf("  Dime detected.\n");
                    break;
                case 'P':
                    total_inserted += COIN3;
                    printf("  Pente detected.\n");
                    break;
                case 'R':
                    change = total_inserted;
                    calculate_change(change);
                    returning = true; 
                    // using continue to skip reporting how much has been inserted
                    continue;
                case 'E':
                    change = total_inserted;
                    // still need go give back what the machine got
                    calculate_change(change);
                    printf("Shutting down. Goodbye.");
                    return 0;
                default:
                    printf("  Unknown coin rejected.\n");
                    break;
            }
            
            printf("    You have inserted a total of %d centimes.\n", total_inserted);

            if (total_inserted < price)
            {
                printf("    Please insert %d more centimes.\n", price - total_inserted);
            }
        }

        if (total_inserted >= price) {
           change = total_inserted - price;
           printf("Pop is dispensed. Thank you for your business! Please come again.\n");
           calculate_change(change);
        }
    }
}
