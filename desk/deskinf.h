/*
 * EmuTOS desktop: header for deskinf.c
 *
 * Copyright (C) 2002-2016 The EmuTOS development team
 *
 * This file is distributed under the GPL, version 2 or at your
 * option any later version.  See doc/license.txt for details.
 */

#ifndef _DESKINF_H
#define _DESKINF_H

WORD dr_code(PARMBLK *pparms);
WORD inf_show(OBJECT *tree, WORD start);
WORD inf_file_folder(BYTE *ppath, FNODE *pf);
WORD inf_disk(BYTE dr_id);
void inf_numset(OBJECT *tree, WORD obj, ULONG value);
WORD inf_pref(void);
WORD opn_appl(BYTE *papname, BYTE *ptail);

#if CONF_WITH_BACKGROUNDS
BOOL inf_backgrounds(void);
#endif

#endif  /* _DESKINF_H */
