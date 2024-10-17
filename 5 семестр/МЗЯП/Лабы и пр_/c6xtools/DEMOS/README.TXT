------------------------------------------------------------------------------
Demos provided with the Release 1.10 of the TMS320C6x Code Generation Tools 
------------------------------------------------------------------------------

TEXAS INSTRUMENTS MICROPROCESSOR DEVELOPMENT TOOLS

Thank you for choosing Texas Instruments software development tools.  It is our
goal to provide you with the most useful and efficient development tools from
which to develop your applications around Texas Instruments processors.

This readme file contains information on how to use all the files found in
subdirectories of demos.  The directory structure of demos looks as follows:

                                 demos 
                                /     \
                          puzzle       prog_gd
                                      /   |    \
                              tutorial  c_code asm_code

Included in this readme file are the descriptions of files in the "c_code" and
"asm_code" subdirectories under the "prog_gd" directory and descriptions of
how to use the TMS320C6x Code Generation Tools Release 1.10 to compile, link,
and run these files.  The files in the "c_code" and "asm_code" subdirectories
are some of the examples used in Chapters 3 and 5 in the TMS320C62xx 
Programmer's Guide.  The .sa and the .asm files in "asm_code" have comments
as to which example that they come from in Chapter 5 of the TMS320C62xx
Programmer's Guide.  The numbers with the .c, .sa, and .asm files in 
"asm_code" correspond to the section in Chapter 5 in which they are used.
 
There is also a subdirectory called "tutorial" under the "prog_gd" directory
that contains the files used in the tutorial in Chapter 2 of the TMS320C62xx
Programmer's Guide.  The instructions on how to use the tutorial files are 
contained in Chapter 2 of the TMS320C62xx Programmer's Guide.

Finally, there is a directory called "puzzle".  This contains the source
and .out file for the code that is used in many of the snapshots of the 
debugger in the TMS320C6x C Source Debugger User's Guide.  The directions
on how to recompile the puzzle program are listed below.

For questions or technical support, please consult your customer support guide
or contact the DSP Hotline at:
 
Email: dsph@ti.com
Phone: (281) 274-2320
Fax:   (281) 274-2324
 
------------------------------------------------------------------------------
 
The "asm_code" and "c_code" subdirectories in the "prog_gd" directory have 
the demo routines that are discussed in the programmer's guide.

Improving performance in C code:
-------------------------------
c_vecsum.c  - Vector sum examples
c_dotp.c    - Dot product examples
c_fir.c     - FIR filter examples
c_firfxd.c  - Fixed tap FIR filter examples

Below is an example of how to compile and run one of these files:

cl6x -qko3 c_dotp.c -z -llnk.cmd -lrts6201.lib -o c_dotp.out
load6x -q c_dotp.out

Programming in assembly:
------------------------
c3_dopt.c  a3_dotp.asm  dotp3.sa, 
c4_dopt.c  a4_dotp.asm  dotp4.sa  - dot product routine.  
c5_wvec.c  a5_wvec.asm  wvec5.sa  - weighted vector sum routine.  
c6_iir.c   a6_iir.asm   iir6.sa   - IIR weighted vector sum routine.
c7_if.c    a7_if.asm    if7.sa    - if-then routine.
c8_unif.c  a8_unif.asm  unif8.sa  - unrolled if-then routine.
c9_live.c  a9_live.asm  live9.sa  - live-too-long routine.
c10_fir.c  a10_fir.asm  fir10.sa, 
c11_fir.c  a11_fir.asm  fir11.sa, 
c12_fir.c  a12_fir.asm,
c13_fir.c  a13_fir.asm  fir13.sa  - finite impulse response filter routine.

Below is an example of how to compile and run one of these examples:

cl6x -qko3 c3_dotp.c dotp3.sa a3_dotp.asm -z -llnk.cmd -l rts6201.lib 
     -o c3_dotp.out
load6x -q c3_dotp.out

Definitions of Some Variables Used in Driver Code
-------------------------------------------------
t_overhead: overhead of two calls to clock() function.
t_stub:     overhead of a stub function call.
t_asm:      cycle count for assembly routine.

Note:  Sample C code that corresponds to each assembly file is contained in
       a comment at the end of each "driver" file.  This will help you
       understand what the assembly loop is doing.

------------------------------------------------------------------------------
How to recreate the puzzle.out (Puzzle Program) in the "puzzle" directory

cl6x -gqo -DPRINT=1 driver.c puzzle.c -z -lrts6201.lib puzzle.cmd -o puzzle.out

Note:  puzzle.cmd is the linker command file for the puzzle program.  Linker
       command files allow you to put linking information into a file, which 
       is useful when you invoke the linker often with the same information.
