@0
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@SP
M=M-1
@R13
M=D
@LCL
D=M
@0
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D
(LOOP)
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@LCL
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@SP
M=M-1
@R14
M=D
@SP
A=M-1
D=M
@SP
M=M-1
@R13
M=D
@R13
D=M
@R14
D=D+M
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@SP
M=M-1
@R13
M=D
@LCL
D=M
@0
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@1
D=A
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@SP
M=M-1
@R14
M=D
@SP
A=M-1
D=M
@SP
M=M-1
@R13
M=D
@R13
D=M
@R14
D=D-M
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@SP
M=M-1
@R13
M=D
@ARG
D=M
@0
D=D+A
@R14
M=D
@R13
D=M
@R14
A=M
M=D
@ARG
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1
@SP
A=M-1
D=M
@SP
M=M-1
@LOOP
D;JNE
@LCL
D=M
@0
A=D+A
D=M
@SP
A=M
M=D
@SP
M=M+1