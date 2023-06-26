#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include "hardware.hpp"

namespace nes {
    void adc(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void _and(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void asl(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void bcc(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void bcs(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void beq(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void bit(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void bne(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void bpl(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void brk(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void bvc(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void bvs(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void clc(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void cld(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void cli(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void clv(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void cmp(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void cpx(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void cpy(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void dec(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void dex(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void dey(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void eor(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void inc(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void inx(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void iny(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void jmp(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void jsr(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void lda(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void ldx(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void ldy(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void lsr(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void nop(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void ora(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void pha(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void php(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void pla(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void plp(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void rol(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void ror(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void rti(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void rts(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void sbc(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void sec(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void sed(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void sei(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void sta(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void stx(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void sty(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void tax(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void tay(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void tsx(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void txa(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void txs(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void tya(struct nes::cpu& cpu, nes::addrMode& addrmode);
}

#endif // INSTRUCTIONS_H_
