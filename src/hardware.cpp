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


// Instrucciones

    void cpu::I_adc() {
        //logica instruccion
        u_int8_t res = acum + valor + VALOR_BIT(status, CARRY_BIT);

        // asignacion de flags
        ASSIGN_BIT(status, OVERFLOW_BIT, ((~(acum ^ valor)) & (acum ^ res) & 0x80) >> 7);
        ASSIGN_BIT(status, CARRY_BIT, res < acum);
        ASSIGN_BIT(status, NEGATIVE_BIT, (res & 0x80) >> 7);
        ASSIGN_BIT(status, CERO_BIT, res == 0);

        // se da el valor al acumulador
        acum = res;

        //se incrementan los ciclos
        if (addresing_mode == Immediate) {ciclos+=2;}

        if (addresing_mode == ZeroPage)  {ciclos+=3;}

        if (addresing_mode == ZeroPageX) {ciclos+=4;}

        if (addresing_mode == Absolute)  {ciclos+=4;}

        if (addresing_mode == AbsoluteX) {
            if (pagina_crusada) ciclos++;
            ciclos+=4;
        }

        if (addresing_mode == AbsoluteY) {
            if (pagina_crusada) ciclos++;
            ciclos+=4;
        }

        if (addresing_mode == IndirectX) {ciclos+=6;}

        if (addresing_mode == IndirectY) {
            if (pagina_crusada) ciclos++;
            ciclos+=5;
        }
    }

    void cpu::I_and() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)
    }

    void cpu::I_asl() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_bcc() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_bcs() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_beq() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_bit() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_bmi() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_bne() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_bpl() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_brk() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_bvc() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_bvs() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_clc() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_cld() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_cli() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_clv() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_cmp() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_cpx() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_cpy() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_dec() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_dex() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_dey() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_eor() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_inc() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_inx() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_iny() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_jmp() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_jsr() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_lda() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_ldx() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_ldy() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_lsr() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_nop() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_ora() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_pha() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_php() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_pla() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_plp() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_rol() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_ror() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_rti() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_rts() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_sbc() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_sec() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_sed() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_sei() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_sta() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_stx() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_sty() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_tax() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_tay() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_tsx() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_txa() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_txs() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }

    void cpu::I_tya() {
        //logica de la instruccion (WIP)

        // asignacion de flags (WIP)

        // Incrementacion de ciclos (WIP)

    }


    void cpu::step(){
        ciclos = 0;
        pagina_crusada = 0;

        u_int8_t cod_op = mem_read(counter++);

        switch (cod_op) {

        // I_adc() add with carry
            case 0x69: {}
            case 0x65: {}
            case 0x75: {}
            case 0x6D: {}
            case 0x7D: {}
            case 0x79: {}
            case 0x61: {}
            case 0x71: {}

        // I_and()
            case 0x29: {}
            case 0x25: {}
            case 0x35: {}
            case 0x2D: {}
            case 0x3D: {}
            case 0x39: {}
            case 0x21: {}
            case 0x31: {}

        // I_asl
            case 0x0A: {}
            case 0x06: {}
            case 0x16: {}
            case 0x0E: {}
            case 0x1E: {}

        // I_bcc()
            case 0x90: {}

        // I_bcs()
            case 0xB0: {}

        // I_beq()
            case 0xF0: {}

        // I_bit()
            case 0x24: {}
            case 0x2C: {}

        // I_bmi()
            case 0x30: {}

        // I_bne()
            case 0xD0: {}

        // I_bpl()
            case 0x10: {}

        // I_brk()
            case 0x00: {}

        // I_bvc()
            case 0x50: {}

        // I_clc()
            case 0x18: {}

        // I_cld()
            case 0xD8: {}

        // I_cli()
            case 0x58: {}

        // I_clv()
            case 0xB8: {}

        // I_cmp()
            case 0xC9: {}
            case 0xC5: {}
            case 0xD5: {}
            case 0xCD: {}
            case 0xDD: {}
            case 0xD9: {}
            case 0xC1: {}
            case 0xD1: {}

        // I_cpx()
            case 0xE0: {}
            case 0xE4: {}
            case 0xEC: {}

        // I_cpy()
            case 0xC0: {}
            case 0xC4: {}
            case 0xCC: {}

        // I_dec()
            case 0xC6: {}
            case 0xD6: {}
            case 0xCE: {}
            case 0xDE: {}

        // I_dex()
            case 0xCA: {}

        // I_dey()
            case 0x88: {}

        // I_eor()
            case 0x49: {}
            case 0x45: {}
            case 0x55: {}
            case 0x4D: {}
            case 0x5D: {}
            case 0x59: {}
            case 0x41: {}
            case 0x51: {}

        // I_inc()
            case 0xE6: {}
            case 0xF6: {}
            case 0xEE: {}
            case 0xFE: {}

        // I_inx()
            case 0xE8: {}

        // I_iny()
            case 0xC8: {}

        // I_jmp()
            case 0x4C: {}
            case 0x6C: {}

        // I_jsr()
            case 0x20: {}

        // I_lda()
            case 0xA9: {}
            case 0xA5: {}
            case 0xB5: {}
            case 0xAD: {}
            case 0xBD: {}
            case 0xB9: {}
            case 0xA1: {}
            case 0xB1: {}

        // I_ldx()
            case 0xA2: {}
            case 0xA6: {}
            case 0xB6: {}
            case 0xAE: {}
            case 0xBE: {}

        // I_ldy()
            case 0xA0: {}
            case 0xA4: {}
            case 0xB4: {}
            case 0xAC: {}
            case 0xBC: {}

        // I_lsr()
            case 0x4A: {}
            case 0x46: {}
            case 0x56: {}
            case 0x4E: {}
            case 0x5E: {}

        // I_nop()
            case 0xEA: {}

        // I_ora()
            case 0x09: {}
            case 0x05: {}
            case 0x15: {}
            case 0x0D: {}
            case 0x1D: {}
            case 0x19: {}
            case 0x01: {}
            case 0x11: {}

        // I_pha()
            case 0x48: {}

        // I_php()
            case 0x08: {}

        // I_pla()
            case 0x68: {}

        // I_plp()
            case 0x28: {}

        // I_rol()
            case 0x2A: {}
            case 0x26: {}
            case 0x36: {}
            case 0x2E: {}
            case 0x3E: {}

        // I_ror()
            case 0x6A: {}
            case 0x66: {}
            case 0x76: {}
            case 0x6E: {}
            case 0x7E: {}

        // I_rti()
            case 0x40: {}

        // I_rts()
            case 0x60: {}

        // I_sbc()
            case 0xE9: {}
            case 0xE5: {}
            case 0xF5: {}
            case 0xED: {}
            case 0xFD: {}
            case 0xF9: {}
            case 0xE1: {}
            case 0xF1: {}

        // I_sec()
            case 0x38: {}

        // I_sed()
            case 0xF8: {}

        // I_sei()
            case 0x78: {}

        // I_sta()
            case 0x85: {}
            case 0x95: {}
            case 0x8D: {}
            case 0x9D: {}
            case 0x99: {}
            case 0x81: {}
            case 0x91: {}

        // I_stx()
            case 0x86: {}
            case 0x96: {}
            case 0x8E: {}

        // I_sty()
            case 0x84: {}
            case 0x94: {}
            case 0x8C: {}

        // I_tax()
            case 0xAA: {}

        // I_tay()
            case 0xA8: {}

        // I_tsx()
            case 0xBA: {}

        // I_txa()
            case 0x8A: {}

        // I_txs()
            case 0x9A: {}

        // I_tya()
            case 0x98: {}
        }
    }
}
