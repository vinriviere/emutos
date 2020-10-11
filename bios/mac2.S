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

        .globl _mac_int_1
_mac_int_1:
        rte

#endif /* MACHINE_MAC */
