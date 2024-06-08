(include "syntax.scm")
(include "ec-evaluator-support.scm")

(define (lexical-address-lookup address env)
  (let ((frame (list-ref env (address-frame address))))
    (let ((value (list-ref (frame-values frame) (address-offset address))))
      (if (eq? value '*unassigned*)
        (error "ERROR: the variable is unassigned -- LEXICAL-ADDRESS-LOOKUP" address)
        value))))

(define (lexical-address-set! value address env)
  (let ((frame (address-frame address))
        (offset (address-offset address)))
    (define (set-var-value! f pos)
      (if (= f 0)
        (set-car! f value)
        (set-var-value! (address-offset f) (- pos 1))))
    (set-var-value! frame offset)))

(define (address-frame address)
  (car address))

(define (address-offset address)
  (cdr address))

(define (lexical-address frame offset)
  (cons frame offset))

(define env (extend-environment '(a b) '(1 2) the-empty-environment))

(display (lexical-address-lookup (lexical-address 0 0) env))
(newline)

(display (lexical-address-lookup (lexical-address 0 1) env))
(newline)

