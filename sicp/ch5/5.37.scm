(include "compiler.scm")

; changes on "preserving" to not optimize the stack
(define (preserving regs seq1 seq2)
  (if (null? regs)
    (append-instruction-sequences seq1 seq2)
    (let ((first-reg (car regs)))
      (preserving (cdr regs)
                  (make-instruction-sequence
                    (list-union (list first-reg)
                                (registers-needed seq1))
                    (list-difference (registers-modified seq1)
                                     (list first-reg))
                    (append `((save ,first-reg))
                            (statements seq1)
                            `((restore ,first-reg))))
                  seq2))))

; compile the procedure from exercise 5.35 and compare the generated code
(define prog '(define (f x)
                (+ x (g (+ x 2)))))

(define code (compile prog 'val 'next))
(pretty-print code)
(newline)
