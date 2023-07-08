//Copyright (c) 2023 federico polidoro. All Rights Reserved.
#include "CPU.hpp"
#include <sys/types.h>

namespace nes {
    cpu::cpu(){
        counter = 0;
        status = 0x24;
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

    void cpu::push(u_int8_t data){
        mem_write(sp + 256, data);
        sp--;
    }

    u_int8_t cpu::pop(){
        sp++;
        return mem_read(sp + 256);
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
        if (addresing_mode == Immediate) ciclos+=2;
        if (addresing_mode == ZeroPage) ciclos+=3;
        if (addresing_mode == ZeroPageX) ciclos+=4;
        if (addresing_mode == Absolute) ciclos+=4;
        if (addresing_mode == AbsoluteX) {
            ciclos+=4;
            if (pagina_crusada) ciclos++;
        }
        if (addresing_mode == AbsoluteY) {
            ciclos+=4;
            if (pagina_crusada) ciclos++;
        }
        if (addresing_mode == IndirectX) {ciclos+=6;}
        if (addresing_mode == IndirectY) {
            ciclos+=5;
            if (pagina_crusada) ciclos++;
        }
    }

    void cpu::I_and() {
        //logica de la instruccion
        acum &= valor;

        // asignacion de flags
        ASSIGN_BIT(status, NEGATIVE_BIT, (acum & 0x80));
        ASSIGN_BIT(status, CERO_BIT, (acum == 0));

        // Incrementacion de ciclos 
        if (addresing_mode == Immediate) ciclos += 2;
        if (addresing_mode == ZeroPage) ciclos += 3;
        if (addresing_mode == ZeroPageX) ciclos += 4;
        if (addresing_mode == Absolute) ciclos += 4;
        if (addresing_mode == AbsoluteX) {
            ciclos += 4;
            if (pagina_crusada) ciclos++;
        }
        if (addresing_mode == AbsoluteY) {
            ciclos += 4;
            if (pagina_crusada) ciclos++;
        }
        if (addresing_mode == IndirectX) ciclos += 6;
        if (addresing_mode == IndirectY) {
            ciclos += 5;
            if (pagina_crusada) ciclos++;
        }
    }
    void cpu::I_asl() {
        //logica de la instruccion
        //NOTE puede que el mem_write() de abajo cause problemas por la addr
        if (addresing_mode == Accumulator){
            acum = asl_val(acum);
        } else {
            valor = asl_val(valor);
            mem_write(direccion, valor);
        }

        // Incrementacion de ciclos
        if (addresing_mode == Accumulator) ciclos += 2;
        if (addresing_mode == ZeroPage) ciclos += 5;
        if (addresing_mode == ZeroPageX) ciclos += 6;
        if (addresing_mode == Absolute) ciclos += 6;
        if (addresing_mode == AbsoluteX) ciclos += 7;
    }

    u_int8_t cpu::asl_val(u_int8_t data) {
        u_int8_t carry = data & 0x80;
        data <<= 1;

        // asignacion de flags
        ASSIGN_BIT(status, CARRY_BIT, carry);
        ASSIGN_BIT(status, NEGATIVE_BIT, data & 0x80);
        ASSIGN_BIT(status, CERO_BIT, data == 0);

        return data;
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
        //logica de la instruccion
        CLEAR_BIT(status, CARRY_BIT);

        // Incrementacion de ciclos (WIP)
        ciclos+=2;
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

        u_int8_t opcode = mem_read(counter++);

        switch (opcode) {

        // I_adc() add with carry
            case 0x69: {AM_IMM(); I_adc();}
            case 0x65: {AM_ZRP(); I_adc();}
            case 0x75: {AM_ZRX(); I_adc();}
            case 0x6D: {AM_ABS(); I_adc();}
            case 0x7D: {AM_ABX(); I_adc();}
            case 0x79: {AM_ABY(); I_adc();}
            case 0x61: {AM_INX(); I_adc();}
            case 0x71: {AM_INY(); I_adc();}

        // I_and()
            case 0x29: {AM_IMM(); I_and();}
            case 0x25: {AM_ZRP(); I_and();}
            case 0x35: {AM_ZRX(); I_and();}
            case 0x2D: {AM_ABS(); I_and();}
            case 0x3D: {AM_ABX(); I_and();}
            case 0x39: {AM_ABY(); I_and();}
            case 0x21: {AM_INX(); I_and();}
            case 0x31: {AM_INY(); I_and();}

        // I_asl
            case 0x0A: {AM_ACC(); I_asl();}
            case 0x06: {AM_ZRP(); I_asl();}
            case 0x16: {AM_ZRX(); I_asl();}
            case 0x0E: {AM_ABS(); I_asl();}
            case 0x1E: {AM_ABX(); I_asl();}

        // I_bcc()
            case 0x90: {AM_REL(); I_bcc();}

        // I_bcs()
            case 0xB0: {AM_REL(); I_bcs();}

        // I_beq()
            case 0xF0: {AM_REL(); I_beq();}

        // I_bit()
            case 0x24: {AM_ZRP(); I_bit();}
            case 0x2C: {AM_ABS(); I_bit();}

        // I_bmi()
            case 0x30: {AM_REL(); I_bmi();}

        // I_bne()
            case 0xD0: {AM_REL(); I_bne();}

        // I_bpl()
            case 0x10: {AM_REL(); I_bpl();}

        // I_brk()
            case 0x00: {AM_IMP(); I_brk();}

        // I_bvc()
            case 0x50: {AM_REL(); I_bvc();}

        // I_bvs()
            case 0x70: {AM_REL(); I_bvs();}

        // I_clc()
            case 0x18: {AM_IMP(); I_clc();}

        // I_cld()
            case 0xD8: {AM_IMP(); I_cld();}

        // I_cli()
            case 0x58: {AM_IMP(); I_cli();}

        // I_clv()
            case 0xB8: {AM_IMP(); I_clv();}

        // I_cmp()
            case 0xC9: {AM_IMM(); I_cmp();}
            case 0xC5: {AM_ZRP(); I_cmp();}
            case 0xD5: {AM_ZRX(); I_cmp();}
            case 0xCD: {AM_ABS(); I_cmp();}
            case 0xDD: {AM_ABX(); I_cmp();}
            case 0xD9: {AM_ABY(); I_cmp();}
            case 0xC1: {AM_INX(); I_cmp();}
            case 0xD1: {AM_INY(); I_cmp();}

        // I_cpx()
            case 0xE0: {AM_IMM(); I_cpx();}
            case 0xE4: {AM_ZRP(); I_cpx();}
            case 0xEC: {AM_ABS(); I_cpx();}

        // I_cpy()
            case 0xC0: {AM_IMM(); I_cpy();}
            case 0xC4: {AM_ZRP(); I_cpy();}
            case 0xCC: {AM_ABS(); I_cpy();}

        // I_dec()
            case 0xC6: {AM_ZRP(); I_dec();}
            case 0xD6: {AM_ZRX(); I_dec();}
            case 0xCE: {AM_ABS(); I_dec();}
            case 0xDE: {AM_ABX(); I_dec();}

        // I_dex()
            case 0xCA: {AM_IMP(); I_dex();}

        // I_dey()
            case 0x88: {AM_IMP(); I_dey();}

        // I_eor()
            case 0x49: {AM_IMM(); I_eor();}
            case 0x45: {AM_ZRP(); I_eor();}
            case 0x55: {AM_ZRX(); I_eor();}
            case 0x4D: {AM_ABS(); I_eor();}
            case 0x5D: {AM_ABX(); I_eor();}
            case 0x59: {AM_ABY(); I_eor();}
            case 0x41: {AM_INX(); I_eor();}
            case 0x51: {AM_INY(); I_eor();}

        // I_inc()
            case 0xE6: {AM_ZRP(); I_inc();}
            case 0xF6: {AM_ZRX(); I_inc();}
            case 0xEE: {AM_ABS(); I_inc();}
            case 0xFE: {AM_ABX(); I_inc();}

        // I_inx()
            case 0xE8: {AM_IMP(); I_inx();}

        // I_iny()
            case 0xC8: {AM_IMP(); I_iny();}

        // I_jmp()
            case 0x4C: {AM_ABS(); I_jmp();}
            case 0x6C: {AM_IND(); I_jmp();}

        // I_jsr()
            case 0x20: {AM_ABS(); I_jsr();}

        // I_lda()
            case 0xA9: {AM_IMM(); I_lda();}
            case 0xA5: {AM_ZRP(); I_lda();}
            case 0xB5: {AM_ZRX(); I_lda();}
            case 0xAD: {AM_ABS(); I_lda();}
            case 0xBD: {AM_ABX(); I_lda();}
            case 0xB9: {AM_ABY(); I_lda();}
            case 0xA1: {AM_INX(); I_lda();}
            case 0xB1: {AM_INY(); I_lda();}

        // I_ldx()
            case 0xA2: {AM_IMM(); I_ldx();}
            case 0xA6: {AM_ZRP(); I_ldx();}
            case 0xB6: {AM_ZRY(); I_ldx();}
            case 0xAE: {AM_ABS(); I_ldx();}
            case 0xBE: {AM_ABY(); I_ldx();}

        // I_ldy()
            case 0xA0: {AM_IMM(); I_ldy();}
            case 0xA4: {AM_ZRP(); I_ldy();}
            case 0xB4: {AM_ZRX(); I_ldy();}
            case 0xAC: {AM_ABS(); I_ldy();}
            case 0xBC: {AM_ABX(); I_ldy();}

        // I_lsr()
            case 0x4A: {AM_ACC(); I_lsr();}
            case 0x46: {AM_ZRP(); I_lsr();}
            case 0x56: {AM_ZRX(); I_lsr();}
            case 0x4E: {AM_ABS(); I_lsr();}
            case 0x5E: {AM_ABX(); I_lsr();}

        // I_nop()
            case 0xEA: {AM_IMP(); I_nop();}

        // I_ora()
            case 0x09: {AM_IMM(); I_ora();}
            case 0x05: {AM_ZRP(); I_ora();}
            case 0x15: {AM_ZRX(); I_ora();}
            case 0x0D: {AM_ABS(); I_ora();}
            case 0x1D: {AM_ABX(); I_ora();}
            case 0x19: {AM_ABY(); I_ora();}
            case 0x01: {AM_INX(); I_ora();}
            case 0x11: {AM_INY(); I_ora();}

        // I_pha()
            case 0x48: {AM_IMP(); I_pha();}

        // I_php()
            case 0x08: {AM_IMP(); I_php();}

        // I_pla()
            case 0x68: {AM_IMP(); I_pla();}

        // I_plp()
            case 0x28: {AM_IMP(); I_plp();}

        // I_rol()
            case 0x2A: {AM_ACC(); I_rol();}
            case 0x26: {AM_ZRP(); I_rol();}
            case 0x36: {AM_ZRX(); I_rol();}
            case 0x2E: {AM_ABS(); I_rol();}
            case 0x3E: {AM_ABX(); I_rol();}

        // I_ror()
            case 0x6A: {AM_ACC(); I_ror();}
            case 0x66: {AM_ZRP(); I_ror();}
            case 0x76: {AM_ZRX(); I_ror();}
            case 0x6E: {AM_ABS(); I_ror();}
            case 0x7E: {AM_ABX(); I_ror();}

        // I_rti()
            case 0x40: {AM_IMP(); I_rti();}

        // I_rts()
            case 0x60: {AM_IMP(); I_rts();}

        // I_sbc()
            case 0xE9: {AM_IMM(); I_sbc();}
            case 0xE5: {AM_ZRP(); I_sbc();}
            case 0xF5: {AM_ZRX(); I_sbc();}
            case 0xED: {AM_ABS(); I_sbc();}
            case 0xFD: {AM_ABX(); I_sbc();}
            case 0xF9: {AM_ABY(); I_sbc();}
            case 0xE1: {AM_INX(); I_sbc();}
            case 0xF1: {AM_INY(); I_sbc();}

        // I_sec()
            case 0x38: {AM_IMP(); I_sec();}

        // I_sed()
            case 0xF8: {AM_IMP(); I_sed();}

        // I_sei()
            case 0x78: {AM_IMP(); I_sei();}

        // I_sta()
            case 0x85: {AM_ZRP(); I_sta();}
            case 0x95: {AM_ZRX(); I_sta();}
            case 0x8D: {AM_ABS(); I_sta();}
            case 0x9D: {AM_ABX(); I_sta();}
            case 0x99: {AM_ABY(); I_sta();}
            case 0x81: {AM_INX(); I_sta();}
            case 0x91: {AM_INY(); I_sta();}

        // I_stx()
            case 0x86: {AM_ZRP(); I_stx();}
            case 0x96: {AM_ZRY(); I_stx();}
            case 0x8E: {AM_ABS(); I_stx();}

        // I_sty()
            case 0x84: {AM_ZRP(); I_sty();}
            case 0x94: {AM_ZRX(); I_sty();}
            case 0x8C: {AM_ABS(); I_sty();}

        // I_tax()
            case 0xAA: {AM_IMP(); I_tax();}

        // I_tay()
            case 0xA8: {AM_IMP(); I_tay();}

        // I_tsx()
            case 0xBA: {AM_IMP(); I_tsx();}

        // I_txa()
            case 0x8A: {AM_IMP(); I_txa();}

        // I_txs()
            case 0x9A: {AM_IMP(); I_txs();}

        // I_tya()
            case 0x98: {AM_IMP(); I_tya();}
        }
    }
}
