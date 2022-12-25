#include "../memory/instruction.h"
#include "../cpu/mmu.h"
#include "../cpu/register.h"

/**
 * 没有模仿CPU对原始的16进制进行decode，而是简单的实现。
 * @param od
 * @return
 */
static uint64_t decode_od(od_t od)
{
    if (od.type == IMM) {
        return od.imm;
    } else if (od.type == REG) {
        /*
         * 为了使用方便，【reg1】定义为指针类型，如果reg1不是指针类型，进行访问的时候比较麻烦，
         * 例如：* (uint64_t *)od.reg1. 先把reg1解释成一个指针类型，再对其进行取指操作。
         * */
        return (uint64_t)od.reg1;
    } else {
        uint64_t vaddr = 0;

        if (od.type == MM_IMM) { // M[Imm]
            vaddr = od.imm;
        } else if (od.type == MM_REG) { // M[R[r_a]]
            vaddr = * (od.reg1);
        } else if (od.type == MM_IMM_REG) { //M[Imm + R[r_b]]
            vaddr = od.imm + *(od.reg1);
        } else if (od.type == MM_REG1_REG2) { // M[R[rb]+R[ri]]
            vaddr = *(od.reg1) + *(od.reg2);
        } else if (od.type == MM_IMM_REG1_REG2) {// M[Imm+R[rb]+R[ri]]
            vaddr = od.imm + *(od.reg1) + *(od.reg2);
        } else if (od.type == MM_REG2_S) { // M[R[ri] \cdot s]
            vaddr = (*(od.reg1)) * od.scale;
        } else if (od.type == MM_IMM_REG2_S) { // M[Imm+R[ri] \cdot s]
            vaddr = od.imm + (*(od.reg2)) * od.scale;
        } else if (od.type == MM_REG1_REG2_S) { // M[R[rb]+R[ri] \cdot s]
            vaddr = *(od.reg1) + od.scale * (* (od.reg2));
        } else if (od.type == MM_IMM_REG1_REG2_S) { // M[Imm+R[rb]+R[ri] \cdot s]
            vaddr = od.imm + *(od.reg1) + od.scale * (*(od.reg2));
        }

        return va2pa(vaddr);
//        uint64_t addr = MM_LEN + 0xff;
//        return mm[addr % MM_LEN];
    }
}

void instruction_cycle()
{
    inst_t* instr = (inst_t *)reg.rip;

    // IF imm THEN imm
    // IF reg THEN reg's value
    // IF MM THEN paddr
    uint64_t src = decode_od(instr->src);
    uint64_t dst = decode_od(instr->dst);

    handler_t handler = handler_table[instr->op];
    handler(src, dst);

}

void init_handler_table()
{
    handler_table[ADD_REG_REG] = &add_reg_reg_handler;
}

void add_reg_reg_handler(uint64_t src, uint64_t dst)
{
    *(uint64_t *)dst = *(uint64_t *)src + *(uint64_t *)dst;
    reg.rip = reg.rip + sizeof(inst_t);
}