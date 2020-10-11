/*
 * mac.c - Macintosh specific functions
 *
 * Copyright (C) 2020 The EmuTOS development team
 *
 * Authors:
 *  VRI   Vincent Rivière
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

/* #define ENABLE_KDEBUG */

#include "emutos.h"
#include "mac.h"
#include "vectors.h"

#ifdef MACHINE_MAC

#define VIA_BASE 0xefe1fe
#define VIA_REG(x) (*(volatile UBYTE*)(VIA_BASE + 512*(x)))

#define VIA_PCR VIA_REG(12) /* Peripheral Control Register */
#define VIA_IER VIA_REG(14) /* Interrupt Enable Register */

#define VIA_IRQ_BIT_SET                 (1<<7)
#define VIA_IRQ_BIT_TIMER1              (1<<6)
#define VIA_IRQ_BIT_TIMER2              (1<<5)
#define VIA_IRQ_BIT_KEYBOARD_CLOCK      (1<<4)
#define VIA_IRQ_BIT_KEYBOARD_DATA_BIT   (1<<3)
#define VIA_IRQ_BIT_KEYBOARD_DATA_READY (1<<2)
#define VIA_IRQ_BIT_VERTICAL_BLANK      (1<<1)
#define VIA_IRQ_BIT_ONE_SECOND          (1<<0)

void mac_kbd_init(void)
{
    VIA_PCR = 0xff;
    //VEC_LEVEL1 = mac_int_1;
    VIA_IER |= (VIA_IRQ_BIT_SET | VIA_IRQ_BIT_KEYBOARD_CLOCK | VIA_IRQ_BIT_KEYBOARD_DATA_BIT);
}

#endif /* MACHINE_MAC */
