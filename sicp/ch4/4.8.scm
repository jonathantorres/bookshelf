(include "metacircular-evaluator.scm")

(define (let? exp)
  (tagged-list? exp 'let))

(define (let-name exp)
  (cadr exp))

(define (let-named-bindings exp)
  (caddr exp))

(define (let-bindings exp)
  (cadr exp))

(define (let-body exp)
  (cddr exp))

(define (let-named-body exp)
  (cdddr exp))

; our updated let->combination transformation to support "named let"
(define (let->combination exp)
  (define (named-let? exp)
    (if (= (length exp) 4)
      true
      false))
  (if (named-let? exp)
    (let ((bindings (map cadr (let-named-bindings exp)))
          (let-names (map car (let-named-bindings exp))))
      (list
        (list 'lambda '()
              (append
                (list 'define (cons (let-name exp) let-names))
                (let-named-body exp))
              (cons (let-name exp) bindings))))
    (let ((lamb (make-lambda (map car (let-bindings exp))
                             (let-body exp))))
      (list lamb (map cadr (let-bindings exp))))))

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
(define fib-prog '(define (fib n)
                     (let fib-iter ((a 1)
                                    (b 0)
                                    (count n))
                       (if (= count 0)
                         b
                         (fib-iter (+ a b) a (- count 1))))))
(define fib-call '(fib 10))

(user-print (eval fib-prog the-global-environment)) (newline)
(user-print (eval fib-call the-global-environment)) (newline)
