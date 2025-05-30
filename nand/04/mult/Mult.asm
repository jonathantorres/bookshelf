// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Mult.asm

// Multiplies R0 and R1 and stores the result in R2.
// (R0, R1, R2 refer to RAM[0], RAM[1], and RAM[2], respectively.)
// The algorithm is based on repetitive addition.

// i = 1
@1
D=A
@i
M=D

// mul = 0
@0
D=A
@mul
M=D

(LOOP)
// if i > R0 goto DONE
@i
D=M
@R0
D=D-M
@DONE
D;JGT

// i = i+1
@i
D=M+1
M=D

// mul = mul+R1
@mul
D=M
@R1
D=D+M
@mul
M=D

@LOOP
0;JMP

(DONE)
// R2 = mul
@mul
D=M
@R2
M=D

(END)
@END
0;JMP

