(include "compiler.scm")

; The order of evaluation is from right to left
; this is done in the construct-arglist procedure by reversing the operand-codes passed to it
; and then evaluating these from left to right.

; changes on construct-arglist and code-to-get-rest-args to evaluate from left to right
(define (construct-arglist operand-codes)
  (let ((operand-codes (reverse operand-codes)))
    (if (null? operand-codes)
      (make-instruction-sequence '() '(argl)
                                 '((assign argl (const ()))))
      (let ((code-to-get-last-arg
              (append-instruction-sequences
                (car operand-codes)
                (make-instruction-sequence '(val) '(argl)
                                           '((assign argl (op list) (reg val)))))))
        (if (null? (cdr operand-codes))
          code-to-get-last-arg
          (preserving '(env)
                      code-to-get-last-arg
                      (code-to-get-rest-args
                        (cdr operand-codes))))))))

(define (code-to-get-rest-args operand-codes)
  (let ((code-for-next-arg
          (preserving '(argl)
                      (car operand-codes)
                      (make-instruction-sequence '(val argl) '(argl)
                                                 '((assign argl
                                                           (op append) (reg val) (reg argl)))))))
    (if (null? (cdr operand-codes))
      code-for-next-arg
      (preserving '(env)
                  code-for-next-arg
                  (code-to-get-rest-args (cdr operand-codes))))))

; compile the factorial procedure for testing
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

