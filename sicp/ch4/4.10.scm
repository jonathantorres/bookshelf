(include "metacircular-evaluator.scm")

; syntax of the language has the procedure name at the end of the list
(define (last i) 
  (if (null? (cdr i)) 
    (car i) 
    (last (cdr i))))
 
(define (tagged-list? exp tag) 
  (if (pair? exp) 
    (eq? (last exp) tag)
    false))

(define (primitive-procedure? proc)
  (eq? (car proc) 'primitive))

(define (operator exp) (last exp))
(define (operands exp) (reverse (cdr (reverse exp))))

; sample program
(define prog '(1 2 3 *))

(user-print (eval prog the-global-environment)) (newline)
  
