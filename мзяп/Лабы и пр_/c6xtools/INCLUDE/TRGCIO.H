/*****************************************************************************/
/*  TRGCIO.H v1.10#                                                          */
/*  Copyright (c) 1995-1997 Texas Instruments Incorporated                   */
/*****************************************************************************/

/*****************************************************************************/
/*  This file contains OTIS-driven CIO constant definitions                  */
/*****************************************************************************/

/*---------------------------------------------------------------------------*/
/* constants for the data transfer functions for the predefined driver       */
/*---------------------------------------------------------------------------*/
#define _DTOPEN    (0xF0)
#define _DTCLOSE   (0xF1)
#define _DTREAD    (0xF2)
#define _DTWRITE   (0xF3)
#define _DTLSEEK   (0xF4)
#define _DTUNLINK  (0xF5)
#define _DTGETENV  (0xF6)
#define _DTRENAME  (0xF7)
#define _DTGETTIME (0xF8)
#define _DTGETCLK  (0xF9)
#define _DTSYNC    (0xFF)

#define CIOBUFSIZ BUFSIZ+32

#if defined(_TMS320C25) || defined(_TMS320C50) || defined(_TMS320C5XX) || defined(_TMS320C2XX)
/*---------------------------------------------------------------------------*/
/* THESE MACROS PACK AND UNPACK SHORTS AND LONGS INTO CHARACTER ARRAYS       */
/*                                                                           */
/* THIS IS DONE BYTE REVERSED TO MAKE THE PC'S JOB EASIER AND SINCE THE      */
/*     DEVICE COULD BE BIG OR LITTLE ENDIAN                                  */
/*---------------------------------------------------------------------------*/
#define LOADSHORT(x,y,z)  { x[(z)]   = (unsigned short) (y); \
                            x[(z)+1] = (unsigned short) (y) >> 8;  }

#define UNLOADSHORT(x,z)   ((short) ( (((long) x[(z)]   << 16) + \
			               ((long) x[(z)+1] << 24)) >> 16))

#define LOAD32(x,y,z) { x[(z)]   = (unsigned long) (y); \
                          x[(z)+1] = (unsigned long) (y) >> 8; \
                          x[(z)+2] = (unsigned long) (y) >> 16;  \
                          x[(z)+3] = (unsigned long) (y) >> 24;   }

#define UNLOAD32(x,z) ( (long) x[(z)]           +  \
                         ((long) x[(z)+1] << 8)   +  \
                         ((long) x[(z)+2] << 16)  +  \
			 ((long) x[(z)+3] << 24))

/*---------------------------------------------------------------------------*/
/* THESE MACROS CAN BE USED TO PACK AND UNPACK CHARACTER STREAMS INTO TARGET */
/* WORDS FOR MORE EFFICIENT TRANSFER.                                        */
/*---------------------------------------------------------------------------*/
#define PACKCHAR(val, base, byte) ( ((byte)%2 == 0) ?  \
	 (*((base) + ((byte)/2))  = ((val) & 0xFF)) : \
	 (*((base) + ((byte)/2)) |= ((val) & 0xFF) << (((byte)%2) * 8)) )

#define UNPACKCHAR(base, byte) \
         ( (*((base) + ((byte)/2)) >> (((byte)%2) * 8)) & 0xFF )

#define BSSCIOBUF 1
#endif /* TMS32025 || TMS32050 || TMS320C5XX (LEAD) */

#if defined(_TMS320C30) || defined(_TMS320C40)
/*---------------------------------------------------------------------------*/
/* THESE MACROS PACK AND UNPACK SHORTS AND LONGS INTO CHARACTER ARRAYS       */
/*                                                                           */
/* THIS IS DONE BYTE REVERSED TO MAKE THE PC'S JOB EASIER AND SINCE THE      */
/*     DEVICE COULD BE BIG OR LITTLE ENDIAN                                  */
/*---------------------------------------------------------------------------*/
#define LOADSHORT(x,y,z)  { x[(z)]   = (unsigned short) (y); \
                            x[(z)+1] = (unsigned short) (y) >> 8;  }

#define UNLOADSHORT(x,z) (((long)((x[(z)] << 16) + (x[(z)+1] << 24))) >> 16)

#define LOAD32(x,y,z) { x[(z)]   = (unsigned long) (y); \
                          x[(z)+1] = (unsigned long) (y) >> 8; \
                          x[(z)+2] = (unsigned long) (y) >> 16;  \
                          x[(z)+3] = (unsigned long) (y) >> 24;   }

#define UNLOAD32(x,z) ((long) (x[(z)]          + (x[(z)+1] << 8) + \
                                (x[(z)+2] << 16) + (x[(z)+3] << 24)))

/*---------------------------------------------------------------------------*/
/* THESE MACROS CAN BE USED TO PACK AND UNPACK CHARACTER STREAMS INTO TARGET */
/* WORDS FOR MORE EFFICIENT TRANSFER.                                        */
/*---------------------------------------------------------------------------*/
#define PACKCHAR(val, base, byte) ( ((byte)%4 == 0) ?  \
	 (*((base) + ((byte)/4))  = ((val) & 0xFF)) : \
	 (*((base) + ((byte)/4)) |= ((val) & 0xFF) << (((byte)%4) * 8)) )

#define UNPACKCHAR(base, byte) \
         ( (*((base) + ((byte)/4)) >> (((byte)%4) * 8)) & 0xFF )

#define BSSCIOBUF 0
#endif  /* TMS32030 */

#if defined(_TMS37016) || defined(_TMS340)
/*---------------------------------------------------------------------------*/
/* THESE MACROS PACK AND UNPACK SHORTS AND LONGS INTO CHARACTER ARRAYS       */
/*                                                                           */
/* THIS IS DONE BYTE REVERSED TO MAKE THE PC'S JOB EASIER AND SINCE THE      */
/*     DEVICE COULD BE BIG OR LITTLE ENDIAN                                  */
/*---------------------------------------------------------------------------*/
#define LOADSHORT(x,y,z)  { x[(z)]   = (unsigned short) (y); \
                            x[(z)+1] = (unsigned short) (y) >> 8;  }

#define UNLOADSHORT(x,z) ((short) ( (short) x[(z)] +             \
				   ((short) x[(z)+1] << 8)))

#define LOAD32(x,y,z) { x[(z)]   = (unsigned long) (y); \
                          x[(z)+1] = (unsigned long) (y) >> 8; \
                          x[(z)+2] = (unsigned long) (y) >> 16;  \
                          x[(z)+3] = (unsigned long) (y) >> 24;   }

#define UNLOAD32(x,z) ( (long) x[(z)]           +  \
                         ((long) x[(z)+1] << 8)   +  \
                         ((long) x[(z)+2] << 16)  +  \
			 ((long) x[(z)+3] << 24))

/*---------------------------------------------------------------------------*/
/* THESE MACROS CAN BE USED TO PACK AND UNPACK CHARACTER STREAMS INTO TARGET */
/* WORDS FOR MORE EFFICIENT TRANSFER.                                        */
/*---------------------------------------------------------------------------*/
#define PACKCHAR(val, base, byte) ( (base)[(byte)] = (val) )

#define UNPACKCHAR(base, byte)    ( (base)[byte] )

#define BSSCIOBUF 1
#endif /* _TMS37016 || _TMS340 */

#if defined(_MVP_PP) || defined(_MVP_MP) || defined(_TMS470) || defined(_TMS370C8) 
/*---------------------------------------------------------------------------*/
/* THESE MACROS PACK AND UNPACK SHORTS AND LONGS INTO CHARACTER ARRAYS       */
/*                                                                           */
/* THIS IS DONE BYTE REVERSED TO MAKE THE PC'S JOB EASIER AND SINCE THE      */
/*     DEVICE COULD BE BIG OR LITTLE ENDIAN                                  */
/*---------------------------------------------------------------------------*/
#define LOADSHORT(x,y,z)  { x[(z)]   = (unsigned short) (y); \
                            x[(z)+1] = (unsigned short) (y) >> 8;  }

#define UNLOADSHORT(x,z) ((short) ( (short) x[(z)] +             \
				   ((short) x[(z)+1] << 8)))

#define LOAD32(x,y,z) { x[(z)]   = (unsigned long) (y); \
                          x[(z)+1] = (unsigned long) (y) >> 8; \
                          x[(z)+2] = (unsigned long) (y) >> 16;  \
                          x[(z)+3] = (unsigned long) (y) >> 24;   }

#define UNLOAD32(x,z) ( (long) x[(z)]           +  \
                         ((long) x[(z)+1] << 8)   +  \
                         ((long) x[(z)+2] << 16)  +  \
			 ((long) x[(z)+3] << 24))

/*---------------------------------------------------------------------------*/
/* THESE MACROS CAN BE USED TO PACK AND UNPACK CHARACTER STREAMS INTO TARGET */
/* WORDS FOR MORE EFFICIENT TRANSFER.                                        */
/*---------------------------------------------------------------------------*/
#define PACKCHAR(val, base, byte) ( (base)[(byte)] = (val) )

#define UNPACKCHAR(base, byte)    ( (base)[byte] )

#define BSSCIOBUF 0
#endif 

#if defined(_TMS320C6X)
/*---------------------------------------------------------------------------*/
/* THESE MACROS PACK AND UNPACK SHORTS AND LONGS INTO CHARACTER ARRAYS       */
/*                                                                           */
/* THIS IS DONE BYTE REVERSED TO MAKE THE PC'S JOB EASIER AND SINCE THE      */
/*     DEVICE COULD BE BIG OR LITTLE ENDIAN                                  */
/*---------------------------------------------------------------------------*/
#define LOADSHORT(x,y,z)  { x[(z)]   = (unsigned short) (y); \
                            x[(z)+1] = (unsigned short) (y) >> 8;  }

#define UNLOADSHORT(x,z) ((short) ( (short) x[(z)] +             \
				   ((short) x[(z)+1] << 8)))

#define LOAD32(x,y,z) { x[(z)]   = (unsigned int) (y); \
                          x[(z)+1] = (unsigned int) (y) >> 8; \
                          x[(z)+2] = (unsigned int) (y) >> 16;  \
                          x[(z)+3] = (unsigned int) (y) >> 24;   }

#define UNLOAD32(x,z) ( (int) x[(z)]           +  \
		       ((int) x[(z)+1] << 8)   +  \
		       ((int) x[(z)+2] << 16)  +  \
		       ((int) x[(z)+3] << 24))

/*---------------------------------------------------------------------------*/
/* THESE MACROS CAN BE USED TO PACK AND UNPACK CHARACTER STREAMS INTO TARGET */
/* WORDS FOR MORE EFFICIENT TRANSFER.                                        */
/*---------------------------------------------------------------------------*/
#define PACKCHAR(val, base, byte) ( (base)[(byte)] = (val) )

#define UNPACKCHAR(base, byte)    ( (base)[byte] )

#define BSSCIOBUF 0
#endif 


