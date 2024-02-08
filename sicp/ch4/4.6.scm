(include "metacircular-evaluator.scm")

(define (let? exp)
  (tagged-list? exp 'let))

(define (let-bindings exp)
  (cadr exp))

(define (let-body exp)
  (cddr exp))

(define (make-application operator operands)
  (cons operator operands))

; our let->combination transformation
(define (let->combination exp)
  (let ((lamb (make-lambda (map car (let-bindings exp))
                           (let-body exp))))
    (make-application lamb (map cadr (let-bindings exp)))))

; our new eval that handles "let" expressions
(define (eval exp env)
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (text-of-quotation exp))
        ((assignment? exp) (eval-assignment exp env))
        ((definition? exp) (eval-definition exp env))
        ((if? exp) (eval-if exp env))
        ((let? exp) (eval (let->combination exp) env))
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

; sample program
(define let-def '(let ((v1 1)
                       (v2 2))
                   (+ v1 v2)))

(user-print (eval let-def the-global-environment)) (newline)

