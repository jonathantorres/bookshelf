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

; a: changes on lookup-variable-value
(define (lookup-variable-value var env)
  (define (env-lookup env)
    (define (scan vars vals)
      (cond ((null? vars)
             (env-lookup (enclosing-environment env)))
            ((eq? var (car vars))
             (if (eq? (car vals) '*unassigned*)
               (error "variable is unassigned" var)
               (car vals)))
            (else (scan (cdr vars) (cdr vals)))))
    (if (eq? env the-empty-environment)
      (error "Unbound variable" var)
      (let ((frame (first-frame env)))
        (scan (frame-variables frame)
              (frame-values frame)))))
  (env-lookup env))

; b: scan-out-defines function
(define (scan-out-defines body)
  (define (name-unassigned defines)
    (map
      (lambda (x) (list (definition-variable x) '*unassigned*))
      defines))
  (define (set-values defines)
    (map (lambda (x)
           (list 'set! (definition-variable x) (definition-value x)))
         defines))
  (define (transform exprs defines not-defines)
    (cond ((null? exprs)
           (if (null? defines)
             body
             (list (list 'let (name-unassigned defines)
                         (make-begin (append (set-values defines)
                                             (reverse not-defines)))))))
          ((definition? (car exprs))
           (transform
             (cdr exprs)
             (cons (car exprs) defines) not-defines))
          (else (transform
                  (cdr exprs)
                  defines (cons (car exprs) not-defines)))))
  (transform body '() '()))

; c: install scan-out-defines into make-procedure
(define (make-procedure parameters body env)
  (list 'procedure parameters (scan-out-defines body) env))

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
(define prog '(let ((v1 1)
                       (v2 2))
                   (+ v1 v2)))

(user-print (eval prog the-global-environment)) (newline)
