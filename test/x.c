#include <stdio.h>

u_int64_t add(u_int64_t a, u_int64_t b)
{
    u_int64_t c = a + b;
    return c;
}

int main() {
    u_int64_t a = 0x1234;
    u_int64_t b = 0xabcd0000;
    u_int64_t c = add(a, b);
    return c;
    //printf("%"c);
}
