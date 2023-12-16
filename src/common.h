#include <stdbool.h>

#define die_msg(...) {printf(__VA_ARGS__"\n"); exit(1);}

#define RAM_BASE_ADDR 0x80000000UL
#define RAM_SIZE_BYTES 0x8000000UL

typedef struct {
    uint32_t regs[32];
    uint32_t pc;
    uint32_t current_pc;
    uint32_t insn_count, insn_count_hi;
    uint32_t exc_cause, exc_val;

    bool s_mode;
    bool sstatus_spp;
    bool sstatus_spie;
    uint32_t sepc;
    uint32_t scause;
    uint32_t stval;
    bool sstatus_mxr;
    bool sstatus_sum;
    bool sstatus_sie;
    uint32_t sie;
    uint32_t sip;
    uint32_t stvec_addr;
    bool stvec_vectored;
    uint32_t sscratch;
    uint32_t scounteren;
    uint32_t satp;
    uint32_t *page_table;

    void *priv;

    void (*mem_fetch)(system cpu, uint32_t addr, uint32_t *value);
    void (*mem_load)(system cpu, uint32_t addr, uint8_t width, uint32_t *value);
    void (*mem_store)(system cpu, uint32_t addr, uint8_t width, uint32_t value);

} core;

typedef struct {
    uint8_t *ram;
    uint8_t *disk;
    // plic plic;
    // uart uart;
    uint32_t timer_lo, timer_hi;
} system;