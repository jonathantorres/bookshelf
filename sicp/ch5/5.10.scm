(include "rm-simulator.scm")

; new syntax: labels are prefixed with a dot (.)
;             registers are prefixed with a @
;             constants are just numbers
(define (register-exp? exp)
  (and
    (symbol? exp)
    (compare-exp? exp "@")))

(define (register-exp-reg exp)
  (sub-exp exp))

(define (constant-exp? exp)
  (number? exp))

(define (constant-exp-value exp)
  exp)

(define (label-exp? exp)
  (and
    (symbol? exp)
    (compare-exp? exp ".")))

(define (label-exp-label exp)
  (sub-exp exp))

(define (sub-exp exp)
  (string->symbol (string-copy (symbol->string exp) 1)))

(define (compare-exp? exp sym)
  (string=?
    (substring (symbol->string exp) 0 1)
    sym))

; exponentiation machine with new syntax
(define expt-machine
  (make-machine
    '(n b product counter)
    (list
      (list '= =) (list '* *) (list '- -))
    '((assign counter @n)
      (assign product 1)
       expt-loop
         (test (op =) @counter 0)
         (branch .expt-done)
         (assign counter (op -) @counter 1)
         (assign product (op *) @b @product)
         (goto .expt-loop)
       expt-done)))

(set-register-contents! expt-machine 'b 2)
(set-register-contents! expt-machine 'n 8)
(start expt-machine)
(display (get-register-contents expt-machine 'product))
(newline)
