/*
 * mac.h - Macintosh specific functions
 *
 * Copyright (C) 2020 The EmuTOS development team
 *
 * Authors:
 *  VRI   Vincent Rivière
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

#ifndef MAC_H
#define MAC_H

#ifdef MACHINE_MAC

void mac_kbd_init(void);

/* The following functions are defined in mac2.S */

void mac_int_1(void);

#endif /* MACHINE_MAC */

#endif /* MAC_H */
