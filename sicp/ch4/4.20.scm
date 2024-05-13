(include "metacircular-evaluator.scm")

(define (let? exp)
  (tagged-list? exp 'let))

(define (let-bindings exp)
  (cadr exp))

(define (let-body exp)
  (cddr exp))

(define (make-application operator operands)
  (cons operator operands))

(define (let->combination exp)
  (let ((lamb (make-lambda (map car (let-bindings exp))
                           (let-body exp))))
    (make-application lamb (map cadr (let-bindings exp)))))

(define (letrec? exp)
  (tagged-list? exp 'letrec))

(define (letrec-list exp)
  (cadr exp))

(define (letrec-body exp)
  (cddr exp))

(define (letrec->combination exp)
  (cons 'let
        (cons
          (map
            (lambda (pair) (list (car pair) ''*unassigned*))
            (letrec-list exp))
          (append
            (map
              (lambda (pair)
                (list 'set! (car pair) (cadr pair)))
              (letrec-list exp))
            (letrec-body exp)))))

(define (eval exp env)
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (text-of-quotation exp))
        ((assignment? exp) (eval-assignment exp env))
        ((definition? exp) (eval-definition exp env))
        ((if? exp) (eval-if exp env))
        ((let? exp) (eval (let->combination exp) env))
        ((letrec? exp) (eval (letrec->combination exp) env))
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
(define prog '(letrec ((fact
                         (lambda (n)
                           (if (= n 1)
                             1
                             (* n (fact (- n 1)))))))
                (fact 10)))

(user-print (eval prog the-global-environment)) (newline)
