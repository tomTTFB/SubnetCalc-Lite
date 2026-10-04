#include <stdio.h>

// %u is a symbol to print an unsigned int32, >> is a bit shift to the right
// and & 255 removes the first 3 segments of the 32 bit number
// 00000000 00000000 11000000 10101000 
// becomes
// 00000000 00000000 00000000 10101000
void print_ip(unsigned int ip) {
    printf("%u.%u.%u.%u\n", ip >> 24, (ip >> 16) & 255, (ip >> 8) & 255, ip & 255);
}

int main(int argc, char **argv) {

    if (argc != 2) {
        printf("Usage: %s 192.168.1.10/24\n", argv[0]);
        return 1;
    }

    unsigned int a = 0, b = 0, c = 0, d = 0, prefix = 0;
    int count = sscanf(argv[1], "%u.%u.%u.%u/%u", &a, &b, &c, &d, &prefix);

    printf("Count: %d\n", count);
    printf("%u %u %u %u /%u\n", a, b, c, d, prefix);
}