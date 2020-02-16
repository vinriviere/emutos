/*
 * hb68k08asm.S - HB68K08 specific assembler functions
 *
 * Copyright (C) 2020 The EmuTOS development team
 *
 * Authors:
 *  VRI   Vincent Rivière
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

#include "asmdefs.h"

/* MFP Timer B interrupt (200 Hz Timer) */
        .globl _hb68k08_int_mfp8
_hb68k08_int_mfp8:
        movem.l d0-d1/a0-a1,-(sp)

// Call vector_5ms.
// As it will return with RTE, we must setup a proper stack frame
        pea     vec5ms_return(pc)       // Return address
        move.w  sr,-(sp)                // SR

        .extern _vector_5ms
        move.l  _vector_5ms,a0
        jmp     (a0)                    // Call the 200 Hz system timer

vec5ms_return:
        move.b  #0xfe,0x000e000f        // Clear Interrupt In Service bit

        movem.l (sp)+,d0-d1/a0-a1
        rte

/* MFP USART interrupt (serial port receive) */
        .globl _hb68k08_int_mfp12
_hb68k08_int_mfp12:
        movem.l d0-d1/a0-a1,-(sp)

        jbsr    _hb68k08_mfp12_interrupt_handler

        movem.l (sp)+,d0-d1/a0-a1
        rte
