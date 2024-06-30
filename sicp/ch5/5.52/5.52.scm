(include "metacircular-evaluator.scm")
(include "compiler.scm")

; compile the metacircular evaluator
(define metacircular-asm (cons
                           '(assign env (op get-global-environment))
                           (statements
                             (compile metacircular-evaluator 'val 'next))))

; output instructions (another script will translate them)
(for-each (lambda (i) (display i) (newline)) metacircular-asm)
