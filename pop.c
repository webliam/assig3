
# 2023-07-19
# pop.c
# Mahnaz Fayezi
# Student ID: 0498765432
# Assignment #3 - Simulate Washing Machine
# CPS 393 Section FB0
# Instructor: L. Hiraki
# Purpose: To simulate operation of automatic washer.
#
# I certify that the program and code are my own work.

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define N 5
#define D 10
#define P 20
#define PRICE_MULT 5
#define MIN_PRICE 30
#define MAX_PRICE 105

void calculate_change(int change) {
    int num_dimes = change / D;
    int num_nickels = (change % D) / N;
    printf("    Change given: %d centimes as %d dime(s) and %d nickel(s).\n", change, num_dimes, num_nickels);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Please specify selling price as a command line argument.\nUsage: pop [price]\n");
        return 1;
    }

    int price = atoi(argv[1]);
    if (price < MIN_PRICE || price > MAX_PRICE) {
        printf("Price must be from %d to %d centimes.\n", MIN_PRICE, MAX_PRICE);
        return 1;
    }
    
    if (price % PRICE_MULT != 0) {
        printf("Price must be a multiple of %d.\n", PRICE_MULT);
        return 1;
    }

    int total_inserted;
    char coin;
    int change;
    bool returning = false;
    printf("Welcome to my C Pop Machine!\n");

    while (1) {
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
                    total_inserted += N;
                    printf("  Nickel detected.\n");
                    break;
                case 'D':
                    total_inserted += D;
                    printf("  Dime detected.\n");
                    break;
                case 'P':
                    total_inserted += P;
                    printf("  Pente detected.\n");
                    break;
                case 'R':
                    change = total_inserted;
                    calculate_change(change);
                    returning = true; 
                    continue;
                case 'E':
                    change = total_inserted;
                    calculate_change(change);
                    printf("Shutting down. Goodbye.");
                    return 0;
                default:
                    printf("  Unknown coin rejected.\n");
                    break;
            }

            if (total_inserted < price)
            {
                printf("    You have inserted a total of %d centimes.\n    Please insert %d more centimes.\n", total_inserted, price - total_inserted);
            }
        }

        if (total_inserted > price) {
           change = total_inserted - price;
           calculate_change(change);
        }
    }
}
