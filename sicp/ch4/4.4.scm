(include "metacircular-evaluator.scm")

(define (and? exp) (tagged-list? exp 'and))
(define (and-expressions exp) (cdr exp))
(define (no-more-expressions? exps) (null? exps))

(define (eval-and exp env)
  (define (loop exps)
    (if (no-more-expressions? exps)
      true
      (let ((value (eval (first-exp exps) env)))
        (if (false? value)
          false
          (loop (rest-exps exps))))))
  (loop (rest-exps exp)))

(define (or? exp) (tagged-list? exp 'or))
(define (or-expressions exp) (cdr exp))

(define (eval-or exp env)
  (define (loop exps)
    (if (no-more-expressions? exps)
      false
      (let ((value (eval (first-exp exps) env)))
        (if (true? value)
          true
          (loop (rest-exps exps))))))
  (loop (rest-exps exp)))

; changes on eval with "and" and "or"
(define (eval exp env)
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (text-of-quotation exp))
        ((assignment? exp) (eval-assignment exp env))
        ((definition? exp) (eval-definition exp env))
        ((if? exp) (eval-if exp env))
        ((and? exp) (eval-and exp env))
        ((or? exp) (eval-or exp env))
        ((lambda? exp)
         (make-procedure (lambda-parameters exp)
                         (lambda-body exp)
                         env))
        ((begin? exp)
         (eval-sequence (begin-actions exp) env))
        ((cond? exp) (eval (cond->if exp) env))
        ((application? exp)
         (apply (eval (operator exp) env)
                (list-of-values (operands exp) env)))
        (else
          (error "Unknown expression type -- EVAL" exp))))

; sample programs
(define p1 '(define truthy (or (= 1 2) (= 1 1))))
(define p2 '(define falsy (and (= 1 2) (= 1 1))))

(user-print (eval p1 the-global-environment)) (newline)
(eval '(display truthy) the-global-environment) (newline)

(user-print (eval p2 the-global-environment)) (newline)
(eval '(display falsy) the-global-environment) (newline)
