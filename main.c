#include <stdio.h>

// %u is a symbol to print an unsigned int32, >> is a bit shift to the right
// and & 255 removes the first 3 segments of the 32 bit number
// 00000000 00000000 11000000 10101000 
// becomes
// 00000000 00000000 00000000 10101000
void print_ip(const char *label, unsigned int ip) {
    printf("%-12s %u.%u.%u.%u\n", label, ip >> 24, (ip >> 16) & 255, (ip >> 8) & 255, ip & 255);
}

void ip_to_str(unsigned int ip, char *out, size_t size) {
    snprintf(out, size, "%u.%u.%u.%u", ip >> 24, (ip >> 16) & 255, (ip >> 8) & 255, ip & 255);
}

int main(int argc, char **argv) {

    if (argc != 2) {
        fprintf(stderr, "Usage: %s 192.168.1.10/24\n", argv[0]);
        return 1;
    }

    unsigned int a = 0, b = 0, c = 0, d = 0, prefix = 0;
    int count = sscanf(argv[1], "%u.%u.%u.%u/%u", &a, &b, &c, &d, &prefix);

    // input validation checks
    if(count != 5) {
        fprintf(stderr, "ERROR: Input not shaped like address\n");
        return 1;
    }
    if(a > 255 || b > 255 || c > 255 || d > 255) {
        fprintf(stderr, "ERROR: Part of address exceeds 255\n");
        return 1;
    }
    if(prefix > 32) {
        fprintf(stderr, "ERROR: Prefix cannot exceed 32\n");
        return 1;
    }

    unsigned int ip = (a << 24) | (b << 16) | (c << 8) | d;

    unsigned int subnetMask = prefix ? 0xFFFFFFFFu << (32 - prefix) : 0;
    unsigned int network = ip & subnetMask;
    unsigned int wildcard = ~subnetMask;
    unsigned int broadcast = network | wildcard;

    print_ip("Address:", ip);
    print_ip("Subnet Mask:", subnetMask);
    print_ip("Network:", network);
    print_ip("Wildcard:", wildcard);
    print_ip("Broadcast:", broadcast);

    unsigned int first;
    unsigned int last;

    if (prefix == 32) {
        first = ip;
        last = ip;
    }
    else if (prefix == 31) {
        first = network;
        last = broadcast;
    }
    else {
        first = network + 1;
        last = broadcast - 1;
    }

    char firstStr[16], lastStr[16];
    ip_to_str(first, firstStr, sizeof firstStr);
    ip_to_str(last, lastStr, sizeof lastStr);

    printf("%-12s %s - %s\n", "Host Range:", firstStr, lastStr);

    printf("\n");

}