#ifndef HARDWARE_STRUCTS_H_
#define HARDWARE_STRUCTS_H_

namespace nes {
    struct cpu {
        short counter;
        unsigned char status;
        unsigned char acum;
        unsigned char sp;
        unsigned char rx;
        unsigned char ry;
        unsigned char mem[500];
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
