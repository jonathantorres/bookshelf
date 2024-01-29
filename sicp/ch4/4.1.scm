(include "metacircular-evaluator.scm")

; list-of-values that evaluates arguments from left to right
(define (list-of-values exps env)
  (if (no-operands? exps)
    '()
    (let ((value (eval (first-operand exps) env))
          (rest (rest-operands exps)))
      (cons value (list-of-values rest env)))))

; list-of-values that evaluates arguments from right to left
(define (list-of-values-right exps env)
  (if (no-operands? exps)
    '()
    (let ((rest (list-of-values-right (rest-operands exps) env))
          (value (eval (first-operand exps) env)))
      (cons value rest))))

; sample program
(define prog '(define (append x y)
                (if (null? x)
                  y
                  (cons (car x)
                        (append (cdr x) y)))))

(user-print (eval prog the-global-environment)) (newline)
(user-print (eval '(append '(a b c) '(d e f)) the-global-environment)) (newline)
