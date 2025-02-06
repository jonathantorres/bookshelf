// This file is part of www.nand2tetris.org
// and the book "The Elements of Computing Systems"
// by Nisan and Schocken, MIT Press.
// File name: projects/4/Fill.asm

// Runs an infinite loop that listens to the keyboard input. 
// When a key is pressed (any key), the program blackens the screen,
// i.e. writes "black" in every pixel. When no key is pressed, 
// the screen should be cleared.

// lim = 8192
@8192
D=A
@lim
M=D

(LOOP)
// if KBD == 0 goto WHITE
@KBD
D=M
@WHITE
D;JEQ

(BLACK)
// i = 1
@1
D=A
@i
M=D

(BLOOP)
// if i == lim goto LOOP
@i
D=M
@lim
D=D-M
@LOOP
D;JGT
@i
D=M-1 // i-1

// SCREEN[i-1] = -1
@SCREEN
A=D+A
M=-1

// i = i+1
@i
D=M+1
M=D
@BLOOP
0;JMP

(WHITE)
// i = 1
@1
D=A
@i
M=D

(WLOOP)
// if i == lim goto LOOP
@i
D=M
@lim
D=D-M
@LOOP
D;JGT
@i
D=M-1 // i-1

// SCREEN[i-1] = 0
@SCREEN
A=D+A
M=0

// i = i+1
@i
D=M+1
M=D
@WLOOP
0;JMP
