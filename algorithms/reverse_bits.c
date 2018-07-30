// https://leetcode.com/problems/reverse-bits/description/

#include <stdint.h>
#include <stdio.h>

uint32_t reverseBits(uint32_t n)
{
    uint32_t rev = 0;

    for (int i = 31; i >= 0; i--) {
        rev |= (((n >> i) & 0x01) << (31 - i));
    }

    return rev;
}

int main() {
    printf("%d\n", reverseBits(43261596));
    return 0;
}
