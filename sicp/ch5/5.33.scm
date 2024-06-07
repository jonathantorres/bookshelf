(include "compiler.scm")
(include "syntax.scm")

; in the procedure call (* (factorial (- n 1)) n)
; the compiler generates a (save argl) and a (restore argl)

; in the procedure call (* n (factorial-alt (- n 1)))
; the compiler generates a (save env) and a (restore env)

; both versions are equally efficient

(define prog '(define (factorial-alt)
                (if (= n 1)
                  1
                  (* n (factorial-alt (- n 1))))))

(define code (compile prog 'val 'next))
(pretty-print code)
(newline)

