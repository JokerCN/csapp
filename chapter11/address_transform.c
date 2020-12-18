#include <arpa/inet.h>
#include <stdio.h>

char dotted_decimal_addr[3][16] = {
    "107.212.122.205",
    "64.12.149.13",
    "107.212.96.29"
};

uint32_t hex_addr[3] = {
    0x00000080,
    0xFFFFFF00,
    0x0A010140
};

int main(){

    uint32_t converted_addr;
    char dotted_buf[16];
    for (size_t i = 0; i < 3; i++)
    {
        inet_pton(AF_INET, dotted_decimal_addr[i], (void*)&converted_addr);
        printf("0x%08X\n", converted_addr);
    }

    for (size_t i = 0; i < 3; i++)
    {
        inet_ntop(AF_INET, &hex_addr[i], dotted_buf, 15);
        printf("%s\n", dotted_buf);
    }
    
    return 0;
}