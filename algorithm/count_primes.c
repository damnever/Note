//
// https://leetcode.com/problems/count-primes/
//

#include <stdio.h>

int countPrimes(int n);

int main()
{
    int count = countPrimes(1500000);
    printf("%d\n", count);
    return 0;
}

int countPrimes(int n)
{
    if(n < 3) return 0;
    int bls[n], i, j, not_prime, count = 0;
    for(i=0; i < n; ++i) {
        bls[i] = 1;
    }
    bls[0] = 0;
    bls[1] = 0;

    for(i=2; i < n; ++i) {
        if(bls[i] == 1) {
            j = 2;
            not_prime = i * j;
            while (not_prime < n) {
                bls[not_prime] = 0;
                j++;
                not_prime = i * j;
            }
        }
    }

    for(i=0; i < n; ++i) {
        count += bls[i];
    }
    return count;
}
