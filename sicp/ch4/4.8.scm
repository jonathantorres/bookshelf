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

(define (make-application operator operands)
  (cons operator operands))

(define (make-let bindings body)
  (list 'let bindings body))

(define (make-definition var value)
  (list 'define var value))


; (define (fib n)
; (define fib-iter (lambda (a b count)
;   (if (= count 0)
;     b
;     (fib-iter (+ a b) a (- count 1)))))

; (((lambda (fib-iter)
;   (lambda (a b count)
;     (if (= count 0)
;       b
;       (fib-iter (+ a b) a (- count 1))))) fib-iter) 1 0 n))

; (display (fib 10)) (newline)


; our updated let->combination transformation to support "named let"
(define (let->combination exp)
  (define (named-let? exp)
    (if (= (length exp) 4)
      true
      false))
  (if (named-let? exp)
    (let ((lamb (make-lambda (list (let-name exp))
                             (make-lambda
                               (map car (let-named-bindings exp))
                               (let-named-body exp)))))
      (let ((inner-lambda (make-lambda
                            (map car (let-named-bindings exp))
                            (let-named-body exp))))
        (make-application   
          (make-application lamb
                            (list (let-name exp)))
          (map cadr (let-named-bindings exp)))))
    (let ((lamb (make-lambda (map car (let-bindings exp))
                             (let-body exp))))
      (make-application lamb (map cadr (let-bindings exp))))))

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

; (define fib-let '(let fib-iter ((a 1)
;                                 (b 0)
;                                 (count n))
;                    (if (= count 0)
;                      b
;                      (fib-iter (+ a b) a (- count 1)))))

(user-print (eval fib-prog the-global-environment)) (newline)
(user-print (eval fib-call the-global-environment)) (newline)
