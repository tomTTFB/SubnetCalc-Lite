#include <stdio.h>

// %u is a symbol to print an unsigned int32, >> is a bit shift to the right
// and & 255 removes the first 3 segments of the 32 bit number
// 00000000 00000000 11000000 10101000 
// becomes
// 00000000 00000000 00000000 10101000
void print_ip(unsigned int ip) {
    printf("%u.%u.%u.%u\n", ip >> 24, (ip >> 16) & 255, (ip >> 8) & 255, ip & 255);
}

int main(void) {
    for (int prefix = 0; prefix <= 32; prefix++) {
        unsigned int mask = prefix ? 0xFFFFFFFFu << (32 - prefix) : 0;
        printf("/%d " , prefix);
        print_ip(mask);
    }
}