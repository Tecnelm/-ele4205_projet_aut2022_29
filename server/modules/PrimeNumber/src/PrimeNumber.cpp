/*
 * PrimeNumber.c
 *
 *  Created on: Jul 17, 2015
 *      Author: 4205_2
 */

#include "PrimeNumber.h"
#include <stdio.h>

#define TAILLE_BUFFER 10

size_t calculate_primes(uint32_t* data, uint32_t max)
{
    int n, o;
    char premier;
    size_t num;

    n = 0;
    num = 0;
    while (n < max) {
        n++;
        premier = 1;

        for (o = 2; o < n && premier; o++)
            premier = ((n % o) != 0);

        if (premier) {
            data[num] = n;
            num = num < 9 ? ++num : 0;
            num++;
        }
    }
    return num;
}

int main_prime_number()
{
    uint32_t primes[TAILLE_BUFFER];
    size_t size, i;
    size = calculate_primes(primes, 1000);
    printf("%i est un nombre premier \n", primes[i]);
    return 0;
}
