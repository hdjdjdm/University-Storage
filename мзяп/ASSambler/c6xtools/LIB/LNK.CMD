/****************************************************************************/
/*  lnk.cmd   v1.10                                                         */
/*  Copyright (c) 1996-1997  Texas Instruments Incorporated                 */
/****************************************************************************/
-c
-heap  0x2000
-stack 0x4000

/* Memory Map 0 - the default */
MEMORY
{
        EXT0:   o = 00000000h   l = 01000000h
        EXT1:   o = 01000000h   l = 00400000h
        PMEM:   o = 01400000h   l = 00010000h 
        EXT2:   o = 02000000h   l = 02000000h
        BMEM:   o = 80000000h   l = 00010000h 
}

/* Memory Map 1 */
/* 
MEMORY
{
        PMEM:   o = 00000000h   l = 00010000h 
        EXT0:   o = 00400000h   l = 01000000h
        EXT1:   o = 01400000h   l = 00400000h
        EXT2:   o = 02000000h   l = 02000000h
        BMEM:   o = 80000000h   l = 00010000h 
} 
*/

SECTIONS
{
    .text       >       PMEM
    .stack      >       BMEM
    .bss        >       BMEM
    .cinit      >       BMEM
    .cio        >       BMEM 
    .const      >       BMEM
    .data       >       BMEM
    .switch     >       BMEM 
    .sysmem     >       BMEM
    .far        >       EXT2
}
