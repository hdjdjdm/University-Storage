/****************************************************************************/
/*  puzzle.cmd                                                              */
/*  Copyright (c) 1996-1997  Texas Instruments Incorporated                 */
/****************************************************************************/
driver.obj
puzzle.obj

-cr
-heap  0x2000
-stack 0x2000

/* for MEMORY MAP = 1 */

MEMORY
{
    VECS:   o = 00000000h       l = 00400h /* reset & interrupt vectors     */
    PMEM:   o = 00000400h	l = 0FC00h /* intended for initialization   */
    BMEM:   o = 80000000h	l = 10000h /* .bss, .system, .stack, .cinit */
}

SECTIONS
{
    vectors     >       VECS
    .text       >       PMEM
    .tables     >       BMEM
    .data       >       BMEM
    .stack	>	BMEM
    .bss	>	BMEM
    .sysmem	>	BMEM
    .cinit	>	BMEM
    .const	>	BMEM
    .cio        >       BMEM 
    .far	>	BMEM 
}
