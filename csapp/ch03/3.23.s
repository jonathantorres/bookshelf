; A: x is in %rdi and then in %rax, y is stored in %rcx and n is stored in %rdx
; B: Using 1(%rcx,%rax),%rax in the leaq instruction, it adds y to x and the constant increases x by one, since p points to x
; C: code below

dw_loop:
    movq    %rdi,%rax              save x
    movq    %rdi,%rcx              y = x
    imulq   %rdi,%rcx              y = x*y
    leaq    (%rdi,%rdi),%rdx       n = 2*x
.L2:
    leaq    1(%rcx,%rax),%rax      x += y and x++
    subq    $1,%rdx                n--
    testq   %rdx,%rdx              test n
    jg      .L2                    jump if n > 0
    rep; ret                       return x, it's stored in %rax
