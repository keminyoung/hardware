#include <stdio.h>
#include "ass.h"

/**
 * 没有对原始的16进制进行decode（而是直接）
 * @param od
 * @return
 */
uint64_t decode(od_t od)
{
    if (od.type == IMM) {
        return od.imm;
    } else if (od.type == REG) {
        return * (uint64_t *)od.reg1;
    } else {
        uint64_t addr = MM_LEN + 0xff;
        return mm[addr % MM_LEN];
    }
}

int main()
{
    cpu_t cpu;
    cpu.rax = 0x1234abcd5678ffff;
    printf("eax: %08x\n", cpu.eax);
    printf("eax: %04x\n", cpu.ax);
    printf("eax: %02x\n", cpu.al);
    printf("eax: %02x\n", cpu.ah);
    return 0;
}