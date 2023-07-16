store_prod:
    movq %rdx, %rax    ; copy bytes of y
    cqto               ; sign extend y
    movq %rsi, %rcx    ; copy bytes of x into %rcx
    sarq $63, %rcx     ; shift right >> 63
    imulq %rax, %rcx   ; y * x
    imulq %rsi, %rdx   ; x * y
    addq %rdx, %rcx    ; x * y + y * x
    mulq %rsi          ; multiply by x (128 bits)
    addq %rcx, %rdx    ; add lower 64 bits
    movq %rax, (%rdi)  ; set low 64 bits
    movq %rdx, 8(%rdi) ; set high 64 bits
