#include <stdio.h>
#include "cpu/register.h"
int main() {
    cpu_t cpu;

    cpu.rax = 0x1234abcd5678ffff;

    printf("eax: %08x\n", cpu.eax);
}
