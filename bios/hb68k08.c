/*
 * hb68k08.c - HB68K08 specific functions
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
#include "hb68k08.h"
#include "mfp.h"
#include "vectors.h"
#include "ikbd.h"

#ifdef MACHINE_HB68K08

#define MFP_BASE        ((MFP *)(0x000e0000L))

void hb68k08_machine_init(void)
{
    /* Disable MFP interrupts */
    MFP_BASE->iera = 0x00;
    MFP_BASE->ierb = 0x00;

    /* Set up vectors and end of interrupt mode */
    MFP_BASE->vr = 0x48; /* Vectors at 0x100, Software End of Interrupt */
}

void hb68k08_init_system_timer(void)
{
    /* We can't use Timer C because it is used for USART Tx.
     * So we use Timer B. */

    /* Set up frequency */
    MFP_BASE->tbcr = 0; /* Disable the timer */
    MFP_BASE->tbdr = 184; /* Counter */
    MFP_BASE->tbcr = 0x07; /* Divide by 200 and enable */

    /* Set up interrupt vector */
    VEC_MFP8 = hb68k08_int_mfp8;

    /* Enable interrupt */
    MFP_BASE->imra |= 0x01;
    MFP_BASE->iera |= 0x01;
}

void hb68k08_usart_init(void)
{
    /* Set up interrupt vector */
    VEC_MFP12 = hb68k08_int_mfp12;

    /* Enable interrupt on USART byte reception */
    MFP_BASE->imra |= 0x10;
    MFP_BASE->iera |= 0x10;
}

BOOL hb68k08_usart_can_write(void)
{
    return !!(MFP_BASE->tsr & 0x80);
}

void hb68k08_usart_write_byte(UBYTE b)
{
    while (!hb68k08_usart_can_write())
    {
        /* Wait */
    }

    /* Send the byte */
    MFP_BASE->udr = b;
}

BOOL hb68k08_usart_can_read(void)
{
    return !!(MFP_BASE->rsr & 0x80);
}

void hb68k08_mfp12_interrupt_handler(void)
{
    while (hb68k08_usart_can_read())
    {
        /* Read the ASCII character */
        UBYTE ascii = MFP_BASE->udr;

        /* And append a new IOREC value into the IKBD buffer */
        push_ascii_ikbdiorec(ascii);
    }

    /* Clear Interrupt In Service Bit */
    MFP_BASE->isra = ~0x10;
}

#endif /* MACHINE_HB68K08 */
