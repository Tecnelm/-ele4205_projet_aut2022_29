/*
 * main.c
 *
 *  Created on: Jul 17, 2015
 *      Author: 4205_2
 */

#include <stdio.h>
#include "PrimeNumber.h"

#define TAILLE_BUFFER 10
int main(int argc,char** argv)
{
	uint32_t primes[TAILLE_BUFFER];
	size_t size, i;

	size = calculate_primes(primes,1000);

	for(i = 0; i < size; i++)
		printf("%i est un nombre premier \n", primes[i]);
	return 0;
}
