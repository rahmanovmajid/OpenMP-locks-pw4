// Exercise 1 - Corrected Parallelized Version
#include <stdio.h>
#include <omp.h>

int main() {

    size_t nb_threads = 0;
    #pragma omp parallel
    {
        #pragma omp critical //or atomic
        nb_threads++;
    }
    printf("nb_threads = %zu\n", nb_threads);

    return 0;
}