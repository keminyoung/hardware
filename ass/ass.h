#include <stdlib.h>
#include <stdint.h>

#define MM_LEN 1000

uint8_t mm[MM_LEN];

typedef struct CPU_STRUCT
{
    union {
        struct {
            uint8_t al;
            uint8_t ah;
        };
        uint16_t ax;
        uint32_t eax;
        uint64_t rax;
    };

    uint64_t rbx;
    uint64_t rcx;
    uint64_t rdx;
    uint64_t rsi;
    uint64_t rdi;
    uint64_t rbp;
    uint64_t rsp;
    uint64_t rip;
    uint64_t r8;
    uint64_t r9;
    uint64_t r10;

} cpu_t;

typedef enum OP {
    MOV, // 0
    PUSH, // 1
    CALL // 2
} op_t;

typedef enum OD_TYPE
{
    IMM, REG, MM_IMM, MM_REG, MM_IMM_REG, MM_REG1_REG2, MM_IMM_REG1_REG2,
    MM_REG2_S, MM_IMM_REG2_S, MM_REG1_REG2_S, MM_IMM_REG1_REG2_S
} od_type_t;

typedef struct OD {
    od_type_t type;

    uint64_t imm;
    uint64_t scale;
    uint64_t reg1;
    uint64_t reg2;
} od_t;

typedef struct INSTRUCT_STRUCT
{
    op_t op;
    od_t src;
    od_t dst;
} inst_t;

#define INST_LEN 100

inst_t program[INST_LEN];

uint64_t decode_od(od_t od);

