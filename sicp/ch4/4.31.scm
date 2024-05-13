(include "lazy-evaluator.scm")

(define (eval exp env)
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (text-of-quotation exp))
        ((assignment? exp) (eval-assignment exp env))
        ((definition? exp) (eval-definition exp env))
        ((if? exp) (eval-if exp env))
        ((lambda? exp)
         (make-procedure (lambda-parameters exp)
                         (lambda-body exp)
                         env))
        ((begin? exp)
         (eval-sequence (begin-actions exp) env))
        ((cond? exp) (eval (cond->if exp) env))
        ((application? exp)
         (apply (eval (operator exp) env)
                (operands exp)
                env))
        (else
         (error "Unknown expression type - EVAL" exp))))

(define (apply procedure arguments env)
  (cond ((primitive-procedure? procedure)
         (apply-primitive-procedure
           procedure
           (list-of-arg-values arguments env)))
        ((compound-procedure? procedure)
         (eval-sequence
           (procedure-body procedure)
           (extend-environment
             (procedure-parameters procedure)
             (list-of-delayed-args (procedure-argument-types procedure) arguments env)
             (procedure-environment procedure))))
        (else
         (error
          "Unknown procedure type - APPLY" procedure))))

(define (list-of-delayed-args types arguments env)
  (map (lambda (type arg) (make-argument type arg env))
       types
       arguments))

(define (make-argument type arg env)
  (cond ((eq? type 'normal) (eval arg env))
        ((eq? type 'lazy) (thunk arg env))
        ((eq? type 'lazy-memo) (memoizable-thunk arg env))
        (error "Unknown parameter type" type)))

(define (procedure-argument-types p)
  (define (type-of parameter)
    (cond ((not (pair? parameter)) 'normal)
          ((eq? (cadr parameter) 'lazy) 'lazy)
          ((eq? (cadr parameter) 'lazy-memo) 'lazy-memo)
          (else (error "Badly formed parameter" parameter))))
  (map type-of (cadr p)))

(define (thunk exp env) (list 'thunk exp env))
(define (memoizable-thunk exp env) (list 'memoizable-thunk exp env))
(define (memoizable-thunk? obj) (tagged-list? obj 'memoizable-thunk))

; sample program
(define prog '(begin
                (define (try a (b lazy))
                  (if (= a 0) 1 b))
                (try 0 (/ 1 0))))

(user-print (eval prog the-global-environment)) (newline)
