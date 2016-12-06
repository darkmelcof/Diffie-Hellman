/**
 * Author : Darkmelcof
 * Alice and Bob share a secret - Diffie-Hellman algorithm
 * 1024-bit value for p
 * TODO : Implement client and server exchange
 **/
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

int main(){
	
	srand(time(NULL));
	
	mpz_t alicePublicResult; mpz_init(alicePublicResult);
	mpz_t bobPublicResult; mpz_init(bobPublicResult);
	mpz_t secretNumber; mpz_init(secretNumber);
	
	mpz_t primeModulus; mpz_init(primeModulus);
	mpz_t generator; mpz_init(generator);
	
	mpz_t a; mpz_init(a);
	mpz_t b; mpz_init(b);

	/* --------------------------------------------
	 * Alice and Bob choose a private secret number 
	 * --------------------------------------------*/
	 
	printf("Alice chooses a secret number :\n");
	gmp_scanf("%Zd", a); 

	printf("Bob chooses a secret number :\n");
	gmp_scanf("%Zd", b);
	
	/* ----------------------------------
	 * Randomize a large primer integer 
	 * ---------------------------------*/
	
	// declaration and initialization
	mpz_t seed; mpz_init(seed);
	gmp_randstate_t state; gmp_randinit_default(state);
	
	// Randomize seed with state
	mpz_set_ui(seed, rand());
	gmp_randseed(state, seed);
	
	// Randomize a 1024-bit value p and g
	mpz_urandomb(primeModulus, state, 1024);
	mpz_urandomb(generator, state, 1024);	
	
	// Check if it is a prime number
	while (mpz_probab_prime_p(primeModulus, 30) != 1)
	{
		mpz_urandomb(primeModulus, state, 1024); 
	}
	
	/* ----------------------------------
	 * 	Compute private numbers
	 * 	---------------------------------*/
	 
	// A = g^a mod p
	mpz_powm(alicePublicResult, generator, a, primeModulus);
	
	// B = g^b mod p
	mpz_powm(bobPublicResult, generator, b, primeModulus);
	
	/* ----------------------------------
	 * 	Compute public results
	 * ----------------------------------*/
	 
	// Alice and Bob private number result from Alice view
	mpz_powm(secretNumber, bobPublicResult, a, primeModulus);
	
	gmp_printf ("Alice and Bob private number result is %Zd\n", secretNumber);

	// Clean up mpz handles
	mpz_clear(seed);
	mpz_clear(alicePublicResult);
	mpz_clear(bobPublicResult);
	mpz_clear(secretNumber);
	mpz_clear(primeModulus);
	mpz_clear(generator);
	mpz_clear(a);
	mpz_clear(b);
	
	return 0;
}
