(include "compiler.scm")

; the difference between the iterative and the recursive versions is that in the recursive version,
; the compiler generates code to (save) the (continue) register and then restores it.
; In the iterative version, the compiler generates code to just (goto) the "val" register.

(define prog '(define (factorial n)
                (define (iter product counter)
                  (if (> counter n)
                    product
                    (iter (* counter product)
                          (+ counter 1))))
                (iter 1 1)))

(define code (compile prog 'val 'next))
(pretty-print code)
(newline)
