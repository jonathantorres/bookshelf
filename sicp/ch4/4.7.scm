(include "metacircular-evaluator.scm")

(define (let? exp)
  (tagged-list? exp 'let))

(define (let*? exp)
  (tagged-list? exp 'let*))

(define (let-bindings exp)
  (cadr exp))

(define (let-body exp)
  (cddr exp))

(define (make-let bindings body)
  (list 'let bindings body))

(define (make-application operator operands)
  (cons operator operands))

(define (let->combination exp)
  (let ((lamb (make-lambda (map car (let-bindings exp))
                           (let-body exp))))
    (make-application lamb (map cadr (let-bindings exp)))))

; our let* using derived expressions, no need to expand it
(define (let*->nested-lets exp)
  (define (nested-lets bindings body)
    (if (last-exp? bindings)
      (make-let (list (first-exp bindings)) (sequence->exp body))
      (make-let
        (list (first-exp bindings))
        (nested-lets (rest-exps bindings) body))))
  (nested-lets (let-bindings exp) (let-body exp)))

; changes on eval to handle "let*"
(define (eval exp env)
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (text-of-quotation exp))
        ((assignment? exp) (eval-assignment exp env))
        ((definition? exp) (eval-definition exp env))
        ((if? exp) (eval-if exp env))
        ((let? exp) (eval (let->combination exp) env))
        ((let*? exp) (eval (let*->nested-lets exp) env))
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

(define let-def '(let* ((x 3)
                        (y (+ x 2))
                        (z (+ x y 5)))
                   (* x z)))

(user-print (eval let-def the-global-environment)) (newline)
