/****************************************************************************/
/*  ieeemask  v1.10                                                           */
/*  Copyright (c) 1997-1997  Texas Instruments Incorporated                 */
/****************************************************************************/

/* This source automatically generated on Wed Jun 4 18:09:57 EDT 1997 */

#ifndef __ieeemask__
#define __ieeemask__

#ifndef BPint
   #error "target properties .h file must be included before ieeemask.h"
#endif

#if 0
/*---------------------------------------------------------------------------*/
/* There are two ways to get at the bits associated with REAL:               */
/*                                                                           */
/* 1. Efficient size-specific casting:                                       */
/*    . for (BPREAL==   BPbigint) use {bigint crx; REALasINT(crx,x); ... etc}*/
/*    . for (BPREAL== 2*BPbigint) use {REAL_2UNS crx; crx.r=x; x.msh ...}    */
/*    These have also been size-abstracted as CREAL (pronounced "Cast REAL") */
/*      {CREAL crx; REALasCREAL(crx,x); ...etc}                              */
/*                                                                           */
/* 2. Slightly less efficient size-independent:                              */
/*       {bigint *pr = (bigint *)(&x)+MSBI_OFFSET;                           */
/*        msbi = *pr;  /* fetch most significant bigint part                 */
/*        NEXT_MS(pr); /* advance ptr to next-most significant bigint part   */
/*    The macros MSI,LSI,MSBI,LSBI will allow access to the most/least       */
/*    significant int/bigint parts without having to declare pr.             */
/*                                                                           */
/* The pointer method is less efficient because most compilers cannot track  */
/* pointer usage sufficiently well to determine the variables changed when   */
/* writing through a pointer.  This causes many keep-it-in-a-register        */
/* opportunities to be lost around write sites.                              */
/* Furthermore, some compilers do not guarantee that reads and writes        */
/* through aliased pointer variables have *ANY* relationship with the        */
/* variables they alias and will optimize code such that desired data        */
/* dependencies are not maintained.  A sometimes-cure for this unfriendly    */
/* behavior is to insert an optmization fence before and after any use of a  */
/* pointer or a pointer cast.  ANSI specifies that char* is itself a fence   */
/* so if the REAL can be processed a char-at-a-time, use the MSC macros.     */
/*                                                                           */
/* Advantages of both models may be obtained by keeping REALs as CREALs      */
/* and using pointers to address of the CREAL version.                       */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* CREAL casting type and associated operations.                          */
/*---------------------------------------------------------------------------*/
#endif
#if (BPREAL == BPbigint)
   union REAL_UNS_u {
      REAL r;
      biguns u;
   };
   typedef union REAL_UNS_u REAL_UNS;
   union REAL_INT_u {
      REAL r;
      bigint i;
   };
   typedef union REAL_INT_u REAL_INT;

 #ifdef Pointers_Might_Not_Work
   #define REALasINT(I, R) do{REAL_INT XX; XX.r =(R); (I)= XX.i;}while (0)
   #define REALasUNS(U, R) do{REAL_UNS XX; XX.r =(R); (U)= XX.u;}while (0)
   #define INTasREAL(R, I) do{REAL_INT XX; XX.i =(I); (R)= XX.r;}while (0)
   #define UNSasREAL(R, U) do{REAL_UNS XX; XX.u =(U); (R)= XX.r;}while (0)

   #define return_REALasINT(R) do{REAL_INT XX; XX.r=(R); return XX.i;}while (0)
   #define return_REALasUNS(R) do{REAL_UNS XX; XX.r=(R); return XX.u;}while (0)
   #define return_INTasREAL(I) do{REAL_INT XX; XX.i=(I); return XX.r;}while (0)
   #define return_UNSasREAL(U) do{REAL_UNS XX; XX.u=(U); return XX.r;}while (0)
 #else
   #define REALasINT(I, R) do{I= *(bigint *)&(R);}while (0)
   #define REALasUNS(U, R) do{U= *(biguns *)&(R);}while (0)
   #define INTasREAL(R, I) do{R= *(REAL *)&(I);}while (0)
   #define UNSasREAL(R, U) do{R= *(REAL *)&(U);}while (0)

   #define return_REALasINT(R) do{REAL mem_REAL=R;\
                                  return *(bigint *)&(mem_REAL);}while (0)
   #define return_REALasUNS(R) do{REAL mem_REAL=R;\
                                  return *(biguns *)&(mem_REAL);}while (0)
   #define return_INTasREAL(I) do{bigint mem_int=I;\
                                  return *(REAL *)&(mem_int);}while (0)
   #define return_UNSasREAL(U) do{biguns mem_uns=U;\
                                  return *(REAL *)&(mem_uns);}while (0)
 #endif

   #define CREAL REAL_UNS
   #define REALasCREAL(CR,R) CR.r=(R)
   #define CREALasREAL(R,CR) (R)=CR.r
   #define UNSasCREAL(CR,U) CR.u=(U)
   #define INTasCREAL(CR,I) CR.i=(I)
   #define CREAL_SAME(l, r) (l==r)

   #define CREAL_IS_NAN(CR) (CR.u>REAL_INFNAN)

#elif (BPREAL==(2*BPbigint))
   union REAL_2UNS_u {
      REAL r;
      struct {
      #if MSB_In_Hi_Addr
         biguns lsh;
         biguns msh;
      #else
         biguns msh;
         biguns lsh;
      #endif
      } u;
   };
   typedef union REAL_2UNS_u REAL_2UNS;
   union REAL_2INT_u {
      REAL r;
      struct {
      #if MSB_In_Hi_Addr
         bigint lsh;
         bigint msh;
      #else
         bigint msh;
         bigint lsh;
      #endif
      } u;
   };
   typedef union REAL_2INT_u REAL_2INT;

#if 0
   /* INTasREAL and UNSasREAL have no meaning unless I,U is *p++ */
#endif
   #if (MSB_In_Hi_Addr)
      #define INTasREAL(R,I) do{LSBI(R)= I; \
                                MSBI(R) = I;} while(0) /* I usually *p++ */
      #define UNSasREAL(R,U) do{LSBI(R)= U; \
                                MSBI(R) = U;} while(0) /* U usually *p++ */
   #else
      #define INTasREAL(R,I) do{MSBI(R)= I; \
                                LSBI(R) = I;} while(0) /* I usually *p++ */
      #define UNSasREAL(R,U) do{MSBI(R)= U; \
                                LSBI(R) = U;} while(0) /* U usually *p++ */
   #endif

   #define CREAL REAL_2UNS
   #define REALasCREAL(CR,R) CR.r=R
   #define CREALasREAL(R,CR) R=CR.r
   #if (MSB_In_Hi_Addr)
      #define UNSasCREAL(CR, U) CR.u.lsh=(U); CR.u.msh=(U)  /* u usually *p++*/
      #define INTasCREAL(CR, I) CR.u.lsh=(biguns)(I); CR.u.msh=(biguns)(I)
   #else
      #define UNSasCREAL(CR, U) CR.u.msh=(u); CR.u.lsh=(U)  /* u usually *p++*/
      #define INTasCREAL(CR, I) CR.u.msh=(biguns)(I); CR.u.lsh=(biguns)(I)
   #endif

   #define CREAL_SAME(l, r) (((l).u.msh == (r).u.msh) && \
                             ((l).u.lsh == (r).u.lsh))

   #define CREAL_IS_NAN(cr) ( ((cr).u.msh> REAL_INFNAN)|| \
                             (((cr).u.msh==REAL_INFNAN)&&((cr).u.lsh>0)))

   
   #define NEG2sCOMP(xx) xx.u.msh = ~xx.u.msh + ((xx.u.lsh = -xx.u.lsh) == 0)

   #define RIGHT_SHIFT(lll, nnn) do { \
      int sc = nnn; \
      if (sc >= BPbigint) {lll.u.lsh= lll.u.msh >> sc-BPbigint; lll.u.msh=0;} \
      else { lll.u.lsh = (lll.u.msh << BPbigint-sc) + (lll.u.lsh >> sc); \
             lll.u.msh >>= sc;}} while (0)

   #define LEFT_SHIFT(lll, nnn) do { \
      int sc = nnn; \
      if (sc >= BPbigint) {lll.u.msh= lll.u.lsh << sc-BPbigint; lll.u.lsh=0;} \
      else { lll.u.msh = (lll.u.lsh >> BPbigint-sc) + (lll.u.msh << sc); \
             lll.u.lsh <<= sc;}} while (0)

   #define RIGHT_SHIFT1(lll) do {\
      lll->u.lsh = (lll->u.lsh >> 1) + (lll->u.msh << BPbigint-1);\
      lll->u.msh >>=1;} while (0)

   #define LEFT_SHIFT1(lll) do {\
      lll->u.msh = (lll->u.msh << 1) + (lll->u.lsh >> BPbigint-1);\
      lll->u.lsh <<=1;} while (0)

   #define RSH1(msh,lsh) \
      do {lsh = (lsh >> 1) + (msh << BPbigint-1); msh >>=1;} while (0)

   #define LSH1(msh,lsh) \
      do {msh = (msh << 1) + (lsh >> BPbigint-1);  lsh <<=1;} while (0)

 #if 0 /* alternative implementations of interest */
   #define RSH1(msh,lsh) \
      do {lsh >>= 1; if (msh & 1) lsh += MINUS; msh >>=1;} while (0)
   #define LSH1(msh,lsh) \
      do {msh <<= 1; if ((int)lsh < 0) msh++; lsh <<=1;} while (0)
 #endif

#else
   #error "no casting type defined for this size REAL"
#endif


#if 0
/*---------------------------------------------------------------------------*/
/* For use with (int *) ptr to REAL, and (bigint *) ptr to REAL.             */
/*    MSC  is "Least Significant   char part"                                */
/*    MSI  is "Least Significant    int part"                                */
/*    MSBI is "Least Significant bigint part"                                */
/*    LSC  is "Least Significant   char part"                                */
/*    LSI  is "Least Significant    int part"                                */
/*    LSBI is "Least Significant bigint part"                                */
/*---------------------------------------------------------------------------*/
#endif

#if 0
/* The C6x compiler exhibits some rather unfriendly this week   */
/* in that it rearranges code with pointer casts such that      */
/* desired data dependencies are not forthcoming and code       */
/* function is unpredictable.  A fix for this is to isolate     */
/* reads and writes and place optimization blocks around them.  */
/* Probably this too will stop working some day.  Beware.       */
#endif
#define OPTIMIZATION_BLOCK asm(" ")

#if (MSB_In_Hi_Addr)
   #define MSC_OFFSET ((BPREAL/BPchar)-1) 
   #define LSC_OFFSET 0
   #define MSI_OFFSET ((BPREAL/BPint)-1) 
   #define LSI_OFFSET 0
   #define MSBI_OFFSET ((BPREAL/BPbigint)-1) 
   #define LSBI_OFFSET 0
   #define NEXT_MS_OFFSET (-1)
   #define CONSUME_MS(ptr) *ptr--
#else
   #define MSC_OFFSET 0
   #define LSC_OFFSET ((BPREAL/BPchar)-1)
   #define MSI_OFFSET 0
   #define LSI_OFFSET ((BPREAL/BPint)-1)
   #define MSBI_OFFSET 0
   #define LSBI_OFFSET ((BPREAL/BPbigint)-1) 
   #define NEXT_MS_OFFSET 1
   #define CONSUME_MS(ptr) *ptr++
#endif

#define LSC(right)  *((  char *)(&right)+ LSC_OFFSET)
#define LSI(right)  *((   int *)(&right)+ LSI_OFFSET)
#define LSBI(right) *((bigint *)(&right)+LSBI_OFFSET)

#define MSC(right)  *((  char *)(&right)+ MSC_OFFSET)
#define MSI(right)  *((   int *)(&right)+ MSI_OFFSET)
#define MSBI(right) *((bigint *)(&right)+MSBI_OFFSET)

#define NEXT_MS(ptr) ptr+=NEXT_MS_OFFSET;

#define SIGN_SET(right) (MSC(right) < 0)
#define MINUSC (((char)1)<<(BPchar-1))




#if 0
/*---------------------------------------------------------------------------*/
/* Masks and constants for the top BPbigint bits of the IEEE number.         */
/*---------------------------------------------------------------------------*/
#endif

#define MINUS (((bigint)1)<<(BPbigint-1))
#define UNORDERED (((int)1)<<(BPint-1)) /* return this for NAN input to CMPF */
#define MASK(bb) ((((bigint)1)<<(bb))-1) /*clear bits above the 2**(bb-1) bit*/

#define REAL_EXP_INFNAN ((((bigint)1)<<REAL_EXP_BITS)-1)
#define REAL_EXP_MASK   ((((bigint)1)<<REAL_EXP_BITS)-1)

#define REAL_FRC_MSBs (REAL_FRC_BITS % BPbigint) /*frc bits MS part*/
#define REAL_FRC_MASK  ((((bigint)1)<< REAL_FRC_MSBs)-1)
#define REAL_HIDDEN_BIT (((bigint)1)<< REAL_FRC_MSBs)
#define REAL_INFNAN (((bigint)REAL_EXP_INFNAN) << REAL_FRC_MSBs)
#define REAL_NSNAN_BIT (((bigint)1)<<(REAL_FRC_MSBs-1)) /* MSB of fraction */
#define REAL_NAN    (REAL_INFNAN+1) /* signalling NAN */
#define REAL_NSNAN  (REAL_INFNAN+REAL_NSNAN_BIT) /*non-signl NAN*/

#define REAL_MOSTPOS (((REAL_EXP_INFNAN-1)<<REAL_FRC_MSBs)+REAL_FRC_MASK)
#define REAL_MOSTNEG (((REAL_EXP_INFNAN-1)<<REAL_FRC_MSBs)+REAL_FRC_MASK+MINUS)


#if 0
/*---------------------------------------------------------------------------*/
/* Similar constants as above,                                               */
/* but defined for LEAN, the next smallest floating point format.            */
/*---------------------------------------------------------------------------*/
#endif
   
#if !defined(LEAN) /* no smaller float size to provide conversion to/from */
   
#elif (BPLEAN == BPbigint)
   union LEAN_UNS_u {
      LEAN r;
      biguns u;
   };
   typedef union LEAN_UNS_u LEAN_UNS;
   union LEAN_INT_u {
      LEAN r;
      bigint i;
   };
   typedef union LEAN_INT_u LEAN_INT;

 #ifdef Pointers_Might_Not_Work
   #define LEANasINT(I, R) do{LEAN_INT XX; XX.r =(R); (I)= XX.i;}while (0)
   #define LEANasUNS(U, R) do{LEAN_UNS XX; XX.r =(R); (U)= XX.u;}while (0)
   #define INTasLEAN(R, I) do{LEAN_INT XX; XX.i =(I); (R)= XX.r;}while (0)
   #define UNSasLEAN(R, U) do{LEAN_UNS XX; XX.u =(U); (R)= XX.r;}while (0)

   #define return_LEANasINT(R) do{LEAN_INT XX; XX.r=(R); return XX.i;}while (0)
   #define return_LEANasUNS(R) do{LEAN_UNS XX; XX.r=(R); return XX.u;}while (0)
   #define return_INTasLEAN(I) do{LEAN_INT XX; XX.i=(I); return XX.r;}while (0)
   #define return_UNSasLEAN(U) do{LEAN_UNS XX; XX.u=(U); return XX.r;}while (0)
 #else
   #define LEANasINT(I, R) do{I= *(bigint *)&(R);}while (0)
   #define LEANasUNS(U, R) do{U= *(biguns *)&(R);}while (0)
   #define INTasLEAN(R, I) do{R= *(LEAN *)&(I);}while (0)
   #define UNSasLEAN(R, U) do{R= *(LEAN *)&(U);}while (0)

   #define return_LEANasINT(R) do{LEAN mem_LEAN=R;\
                                  return *(bigint *)&(mem_LEAN);}while (0)
   #define return_LEANasUNS(R) do{LEAN mem_LEAN=R;\
                                  return *(biguns *)&(mem_LEAN);}while (0)
   #define return_INTasLEAN(I) do{bigint mem_int=I;\
                                  return *(LEAN *)&(mem_int);}while (0)
   #define return_UNSasLEAN(U) do{biguns mem_uns=U;\
                                  return *(LEAN *)&(mem_uns);}while (0)
 #endif

   #define CLEAN LEAN_UNS
   #define LEANasCLEAN(CR,R) CR.r=(R)
   #define CLEANasLEAN(R,CR) (R)=CR.r
   #define UNSasCLEAN(CR,U) CR.u=(U)
   #define INTasCLEAN(CR,I) CR.i=(I)
   #define CLEAN_SAME(l, r) (l==r)

   #define LEAN_IS_NAN(CR) (CR.u>LEAN_INFNAN)

#elif (BPLEAN==(2*BPbigint))
   #define INTasLEAN(r,i) do{int j; bigint *q = &r; \  /* i usually *p++ */
                             for (j=1; j<=BPLEAN/BPbigint; j++)\
                                *q++ = i;}while(0)
   #define UNSasLEAN(r,u) do{int j; biguns *q = &r; \  /* u usually *p++ */
                             for (j=1; j<=BPLEAN/BPbigint; j++)\
                                *q++ = u;}while(0)

   union LEAN_2UNSs_u {
      LEAN r;
      struct {
      #if MSB_In_Hi_Addr
         biguns lsh;
         biguns msh;
      #else
         biguns msh;
         biguns lsh;
      #endif
      } u;
   };
   typedef union LEAN_2UNSs_u LEAN_2UNSs;

   #define CLEAN LEAN_2UNSs
   #define LEANasCLEAN(cr,R) cr.r=R
   #define CLEANasLEAN(R,cr) R=cr.r
   #if (MSB_In_Hi_Addr)
      #define UNSasCLEAN(cr, u) cr.u.lsh=(u); cr.u.msh=(u) /*u usually *p++*/
      #define INTasCLEAN(cr, i) cr.u.lsh=(biguns)(i); cr.u.msh=(biguns)(i)
   #else
      #define UNSasCLEAN(cr, u) cr.u.msh=(u); cr.u.lsh=(u) /*u usually *p++*/
      #define INTasCLEAN(cr, i) cr.u.msh=(biguns)(i); cr.u.lsh=(biguns)(i)
   #endif

   #define CLEAN_SAME(l, r) (((l).u.msh == (r).u.msh) && \
                             ((l).u.lsh == (r).u.lsh))

   #define CLEAN_IS_NAN(cr) ( ((cr).u.msh> LEAN_INFNAN)|| \
                             (((cr).u.msh==LEAN_INFNAN)&&((cr).u.lsh>0)))
#else
   #error "no casting type defined for this size LEAN format"
#endif


#define LEAN_EXP_INFNAN ((((bigint)1)<<LEAN_EXP_BITS)-1)
#define LEAN_EXP_MASK ((((bigint)1)<<LEAN_EXP_BITS)-1)

#define LEAN_EXP_INFNAN ((((bigint)1)<<LEAN_EXP_BITS)-1)
#define LEAN_EXP_MASK   ((((bigint)1)<<LEAN_EXP_BITS)-1)

#define LEAN_FRC_MSBs (LEAN_FRC_BITS % BPbigint) /*frc bits MS part*/
#define LEAN_FRC_MASK  ((((bigint)1)<< LEAN_FRC_MSBs)-1)
#define LEAN_HIDDEN_BIT (((bigint)1)<< LEAN_FRC_MSBs)
#define LEAN_INFNAN (((bigint)LEAN_EXP_INFNAN) << LEAN_FRC_MSBs)
#define LEAN_NSNAN_BIT (((bigint)1)<<(LEAN_FRC_MSBs-1)) /* MSB of fraction */
#define LEAN_NAN    (LEAN_INFNAN+1) /* signalling NAN */
#define LEAN_NSNAN  (LEAN_INFNAN+LEAN_NSNAN_BIT) /*non-signl NAN*/

#endif /* __ieeemask__ */
