// Exercise 2 - Parallelized Version
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <omp.h>

#define PRIME_MIN 3
#define PRIME_MAX 101

int main() {
    size_t primes[PRIME_MAX];
    size_t nb_primes = 0;
    size_t i, divisor;
    bool is_prime;
    
    #pragma omp parallel private(divisor,is_prime)
    {
        #pragma omp for ordered
        for (i = PRIME_MIN; i < PRIME_MAX; i += 2) {
            #pragma omp ordered
            {
                is_prime = true;
                divisor = PRIME_MIN;            
                while((divisor < i) && is_prime) {
                    if ((i % divisor) == 0) { is_prime = false; }
                    divisor += 2;
                }
                if (is_prime) {
                    #pragma omp critical
                    {
                        primes[nb_primes] = i;
                        nb_primes++;
                    }
                }
            }
        }
    }   

    printf("\nNumber of Primes = %zu ~ (Between %d and %d)\n",nb_primes,PRIME_MIN, PRIME_MAX);

    for ( int a = 0; a < nb_primes; a++ ) {
        printf("%zu, ",primes[a]);
    }

    puts("\n");
    return 0;
}