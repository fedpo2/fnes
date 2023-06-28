#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include "hardware.hpp"

namespace nes {
    short get_addr(nes::addrMode mode);
    void I_adc(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_and(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_asl(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_bcc(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_bcs(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_beq(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_bit(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_bne(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_bpl(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_brk(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_bvc(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_bvs(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_clc(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_cld(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_cli(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_clv(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_cmp(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_cpx(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_cpy(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_dec(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_dex(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_dey(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_eor(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_inc(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_inx(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_iny(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_jmp(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_jsr(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_lda(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_ldx(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_ldy(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_lsr(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_nop(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_ora(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_pha(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_php(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_pla(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_plp(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_rol(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_ror(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_rti(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_rts(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_sbc(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_sec(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_sed(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_sei(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_sta(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_stx(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_sty(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_tax(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_tay(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_tsx(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_txa(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_txs(struct nes::cpu& cpu, nes::addrMode& addrmode);
    void I_tya(struct nes::cpu& cpu, nes::addrMode& addrmode);
}

#endif // INSTRUCTIONS_H_
