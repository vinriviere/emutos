/*
 * mac2.S - Macintosh specific assembler functions
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

#ifdef MACHINE_MAC

        .extern _int_vbl
        .extern _mac_extra_vbl

        .globl _mac_int_1
_mac_int_1:
        movem.l d0-d1/a0-a1,-(sp)

        move.b  0xeffbfe,d0             // Interrupt Flag Register
        btst    #1,d0                   // VBL interrupt?
        jeq     macvblend

// VBL interrupt
        jbsr    _int_vbl                // Call the standard VBL handler
        jbsr    _mac_extra_vbl          // Call extra VBL handler
        move.b  #0x02,0xeffbfe          // Clear Interrupt Flag

macvblend:
        movem.l (sp)+,d0-d1/a0-a1
        rte

#endif /* MACHINE_MAC */
