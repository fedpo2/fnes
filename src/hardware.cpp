#include "hardware.hpp"
#include "instructions.hpp"
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

// AM_
//

    void cpu::AM_IMP() {
        addresing_mode = Implicit;
    }

    void cpu::AM_ACC() {
        valor = acum;
        addresing_mode = Accumulator;
    }

    void cpu::AM_IMM() {
        direccion = counter++;
        valor = mem_read(direccion);
        addresing_mode = Immediate;
    }

    void cpu::AM_ZRP() {
        direccion = mem_read(counter++);
        valor = mem_read(direccion);
        addresing_mode = ZeroPage;
    }

    void cpu::AM_ZRX() {
        direccion = mem_read(counter++) + rx;
        valor = mem_read(direccion);
        addresing_mode = ZeroPageX;
    }

    void cpu::AM_ZRY() {
        direccion = mem_read(counter++) + ry;
        valor = mem_read(direccion);
        addresing_mode = ZeroPageY;
    }

    void cpu::AM_REL() {
        direccion = counter;
        valor = mem_read(direccion);
        addresing_mode = Relative;
    }

    void cpu::AM_ABS() {
        if ((counter & 0xff) == 0xff) pagina_crusada = 1;
        direccion = mem_read(counter) & (mem_read(counter + 1) << 8);
        valor = mem_read(direccion);
        counter += 2;
        addresing_mode = Absolute;
    }

    void cpu::AM_ABX() {
        if ((counter & 0xff) == 0xff) pagina_crusada = 1;
        direccion = (mem_read(counter) & (mem_read(counter + 1) << 8) + rx);
        valor = mem_read(direccion);
        counter += 2;
        addresing_mode = AbsoluteX;
    }

    void cpu::AM_ABY() {
        direccion = (mem_read(counter) & (mem_read(counter + 1) << 8) + ry);
        valor = mem_read(direccion);
        counter += 2;
        addresing_mode = AbsoluteY;

    }

    void cpu::AM_IND() {
        if ((counter & 0xff) == 0xff) pagina_crusada = 1;
        direccion = mem_read(counter) & (mem_read(counter + 1) << 8);
        valor = mem_read(direccion);
        counter += 2;
        addresing_mode = Indirect;
    }

    void cpu::AM_INX() {
        if ((counter & 0xff) == 0xff) pagina_crusada = 1;
        direccion = mem_read((u_int8_t)(mem_read(counter) + rx)) & (mem_read((u_int8_t)(mem_read(counter) + rx + 1)) << 8);
        valor = mem_read(direccion);
        counter++;
        addresing_mode = IndirectX;
    }

    void cpu::AM_INY() {
        direccion = (mem_read(mem_read(counter)) & (mem_read(mem_read(counter) + 1) << 8)) + ry;
        valor = mem_read(direccion);
        counter++;
        addresing_mode = IndirectY;
    }

    void cpu::step(){
        ciclos = 0;
        pagina_crusada = 0;

        u_int8_t cod_op = mem_read(counter++);

        // I_adc() add with carry
        switch (cod_op) {

        }
    }
}
