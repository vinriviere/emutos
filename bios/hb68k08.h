/*
 * hb68k08.h - HB68K08 specific functions
 *
 * Copyright (C) 2020 The EmuTOS development team
 *
 * Authors:
 *  VRI   Vincent Rivière
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

#ifndef HB68K08_H
#define HB68K08_H

#ifdef MACHINE_HB68K08

void hb68k08_machine_init(void);
void hb68k08_init_system_timer(void);
void hb68k08_usart_init(void);
BOOL hb68k08_usart_can_write(void);
void hb68k08_usart_write_byte(UBYTE b);
BOOL hb68k08_usart_can_read(void);

void hb68k08_int_mfp8(void); /* In hb68k08asm.S */
void hb68k08_int_mfp12(void); /* In hb68k08asm.S */
void hb68k08_mfp12_interrupt_handler(void);

#endif /* MACHINE_HB68K08 */

#endif /* HB68K08_H */
