#include "hardware.hpp"
#include <sys/types.h>
namespace nes {
    cpu::cpu(){
        counter = 0;
        status = 0;
        acum = 0;
        sp = nes::START_STACK_POINTER;
        rx = 0;
        ry = 0;
    }

    u_int8_t cpu::mem_read(u_int16_t addr){
        return mem[addr];

    }

    void cpu::mem_write(u_int16_t addr, u_int8_t data){
        mem[addr] = data;
    }

    u_int16_t cpu::mem_read_u16(u_int16_t addr){
        u_int16_t lo = (u_int16_t) mem_read(addr);
        u_int16_t hi = (u_int16_t) mem_read(addr+1);
        hi = hi << 8;
        hi |= lo;
        return hi;
    }

}
