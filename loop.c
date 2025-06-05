#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <openssl/sha.h>

#define LOOP_ITERATIONS 1000000
#define BLOCK_SIZE 1024

void print_time(const char* label, struct timespec start, struct timespec end) {
    double elapsed = (end.tv_sec - start.tv_sec) +
                     (end.tv_nsec - start.tv_nsec) / 1e9;
    printf("%s elapsed: %.4f seconds\n", label, elapsed);
}

void sha256_random_block() {
    unsigned char data[BLOCK_SIZE];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Fill with random bytes
    for (int i = 0; i < BLOCK_SIZE; i++) {
        data[i] = rand() % 256;
    }

    // Compute hash
    SHA256(data, BLOCK_SIZE, hash);
}

void loop_not_unrolled() {
    for (int i = 0; i < 4 * LOOP_ITERATIONS; i++) {
        sha256_random_block();
    }
}

void loop_unrolled() {
    for (int i = 0; i < LOOP_ITERATIONS; i++) {
        sha256_random_block();
        sha256_random_block();
        sha256_random_block();
        sha256_random_block();
    }
}

int main() {
    srand(time(NULL)); // Seed random generator

    struct timespec start, end;

    // loop_not_unrolled
    clock_gettime(CLOCK_MONOTONIC, &start);
    loop_not_unrolled();
    clock_gettime(CLOCK_MONOTONIC, &end);
    print_time("loop_not_unrolled", start, end);

    // loop_unrolled
    clock_gettime(CLOCK_MONOTONIC, &start);
    loop_unrolled();
    clock_gettime(CLOCK_MONOTONIC, &end);
    print_time("loop_unrolled", start, end);

    return 0;
}
