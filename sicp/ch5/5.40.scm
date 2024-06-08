(include "compiler-env.scm")

; this version of the compiler is used in subsequent exercises
; most of the changes for this exercise are done in compiler-env.scm
; so that it can be reused

; compile the factorial procedure for testing
(define prog '(define (factorial n)
                (if (= n 1)
                  1
                  (* n (factorial (- n 1))))))

(define code (compile prog 'val 'next '()))
(pretty-print code)
(newline)
