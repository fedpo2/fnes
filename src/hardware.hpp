#ifndef HARDWARE_STRUCTS_H_
#define HARDWARE_STRUCTS_H_

#include <sys/types.h>

#define NEGATIVE_BIT 7
#define OVERFLOW_BIT 6
#define BREAK_BIT    4
#define DECIMAL_BIT  3
#define INT_BIT      2
#define CERO_BIT     1
#define CARRY_BIT    0

#define ESTADO_NEGATIVO  (1 << NEGATIVE_BIT)
#define ESTADO_OVERFLOW  (1 << OVERFLOW_BIT)
#define ESTADO_BREAK     (1 << BREAK_BIT)
#define ESTADO_DECIMAL   (1 << DECIMAL_BIT)
#define ESTADO_INTERRUPT (1 << INT_BIT)
#define ESTADO_CERO      (1 << CERO_BIT)
#define ESTADO_CARRY     CARRY_BIT

#define VALOR_BIT(b,i) ((b & (1 << i)) >> i)
#define SET_BIT(b,i) b |= (1 << i)
#define CLEAR_BIT(b,i) b &= ~(1 << i)
#define ASSIGN_BIT(b,i,v) if (v) { SET_BIT(b,i); } else { CLEAR_BIT(b,i); }

namespace nes {
    const u_int16_t MEM_SIZE = 0xffff;
    const u_int16_t RESET_INT_ADDR = 0xfffc;
    const u_int16_t ROM_ADDR_START = 0x0600;
    const u_int8_t START_STACK_POINTER = 0xff;

    class cpu {
        public:
            cpu();
            u_int8_t mem_read(u_int16_t);
            void mem_write(u_int16_t, u_int8_t);
            u_int16_t mem_read_u16(u_int16_t); // NOTE: si no termina siendo útil talvez la borre

            void push(u_int8_t);
            u_int8_t pop();

            void step();
        public:
            u_int16_t counter;
            u_int8_t status;
            u_int8_t acum;
            u_int8_t sp;
            u_int8_t rx;
            u_int8_t ry;
        private:
            u_int8_t mem[MEM_SIZE];

    };

    enum addrMode {
        Accumulator,
        Relative,
        Immediate,
        ZeroPage,
        ZeroPageX,
        ZeroPageY,
        Absolute,
        AbsoluteX,
        AbsoluteY,
        IndirectX,
        IndirectY,
        NoneAddressing
    };
}

#endif // HARDWARE_STRUCTS_H_
