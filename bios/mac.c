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
#include "delay.h"
#include "asm.h"

#ifdef MACHINE_MAC

#define VIA_BASE 0x00efe1fe
#define VIA_REG(x) (*(volatile UBYTE*)(VIA_BASE + 0x200*(x)))

#define VIA_BUFB VIA_REG(0)  /* Register B */
#define VIA_PCR  VIA_REG(12) /* Peripheral Control Register */
#define VIA_IER  VIA_REG(14) /* Interrupt Enable Register */
#define VIA_BUFA VIA_REG(15) /* Register A */

#define VIA_IRQ_BIT_SET                 (1<<7)
#define VIA_IRQ_BIT_TIMER1              (1<<6)
#define VIA_IRQ_BIT_TIMER2              (1<<5)
#define VIA_IRQ_BIT_KEYBOARD_CLOCK      (1<<4)
#define VIA_IRQ_BIT_KEYBOARD_DATA_BIT   (1<<3)
#define VIA_IRQ_BIT_KEYBOARD_DATA_READY (1<<2)
#define VIA_IRQ_BIT_VERTICAL_BLANK      (1<<1)
#define VIA_IRQ_BIT_ONE_SECOND          (1<<0)

#define VIA_REGB_SW (1<<3) /* Mouse switch */

#define SCC_RBASE 0x009ffff8
#define SCC_WBASE 0x00bffff9

struct SCC
{
    UBYTE bCtl;         /* channel B control */
    UBYTE filler01;
    UBYTE aCtl;         /* channel A control */
    UBYTE filler03;
    UBYTE bData;        /* channel B data in or out */
    UBYTE filler05;
    UBYTE aData;        /* channel A data in or out */
    UBYTE filler07;
};

#define SCCR (*(volatile struct SCC*)SCC_RBASE)
#define SCCW (*(volatile struct SCC*)SCC_WBASE)

#define scc_delay()    // delay_loop(loopcount_1_msec*100);

static UBYTE scc_read_a(UBYTE reg)
{
    SCCR.aCtl = reg;
    scc_delay();
    return SCCR.aCtl;
}

static void scc_write_a(UBYTE reg, UBYTE data)
{
    SCCW.aCtl = reg;
    scc_delay();
    SCCW.aCtl = data;
    scc_delay();
}

static UBYTE scc_read_b(UBYTE reg)
{
    SCCR.bCtl = reg;
    scc_delay();
    return SCCR.bCtl;
}

static void scc_write_b(UBYTE reg, UBYTE data)
{
    SCCW.bCtl = reg;
    scc_delay();
    SCCW.bCtl = data;
    scc_delay();
}

void mac_kbd_init(void)
{
    MAYBE_UNUSED(scc_read_a);
    MAYBE_UNUSED(scc_write_a);
    MAYBE_UNUSED(scc_read_b);
    MAYBE_UNUSED(scc_write_b);

    VEC_LEVEL1 = mac_int_1;
    VIA_IER = VIA_IRQ_BIT_SET | VIA_IRQ_BIT_VERTICAL_BLANK;

    /* Mini vMac requires the SCC MIE bit to be enabled to produce mouse events.
     * See src/MOUSEMDV.c and Mouse_Enabled in Mini vMac sources. */
    scc_write_b(9, 0x08);
}

/******************************************************************************/
/* Mouse                                                                      */
/******************************************************************************/

static void mac_mouse_button_vbl(void)
{
    BOOL button;

    button = !(VIA_BUFB & VIA_REGB_SW);
    *(ULONG*)0xFA700 = button; // Debug Screen Pixel : OK
}

/******************************************************************************/
/* Extra VBL                                                                  */
/******************************************************************************/

void mac_extra_vbl(void)
{
    mac_mouse_button_vbl();
}

#endif /* MACHINE_MAC */
