#ifndef INSTRUCTIONS_H_
#define INSTRUCTIONS_H_

#include "hardware.hpp"

namespace nes {
    short get_addr(nes::addrMode mode);
    void I_adc();
    void I_and();
    void I_asl();
    void I_bcc();
    void I_bcs();
    void I_beq();
    void I_bit();
    void I_bmi();
    void I_bne();
    void I_bpl();
    void I_brk();
    void I_bvc();
    void I_bvs();
    void I_clc();
    void I_cld();
    void I_cli();
    void I_clv();
    void I_cmp();
    void I_cpx();
    void I_cpy();
    void I_dec();
    void I_dex();
    void I_dey();
    void I_eor();
    void I_inc();
    void I_inx();
    void I_iny();
    void I_jmp();
    void I_jsr();
    void I_lda();
    void I_ldx();
    void I_ldy();
    void I_lsr();
    void I_nop();
    void I_ora();
    void I_pha();
    void I_php();
    void I_pla();
    void I_plp();
    void I_rol();
    void I_ror();
    void I_rti();
    void I_rts();
    void I_sbc();
    void I_sec();
    void I_sed();
    void I_sei();
    void I_sta();
    void I_stx();
    void I_sty();
    void I_tax();
    void I_tay();
    void I_tsx();
    void I_txa();
    void I_txs();
    void I_tya();
}

#endif // INSTRUCTIONS_H_
