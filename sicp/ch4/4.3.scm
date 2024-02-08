(include "table.scm")
(include "metacircular-evaluator.scm")

; installing operations
(put 'eval 'quote (lambda (exp env)
     (text-of-quotation exp)))

(put 'eval 'set (lambda (exp env)
     (eval-assignment exp env)))

(put 'eval 'define (lambda (exp env)
     (eval-definition exp env)))

(put 'eval 'if (lambda (exp env)
     (eval-if exp env)))

(put 'eval 'lambda (lambda (exp env)
     (make-procedure (lambda-parameters exp)
                     (lambda-body exp)
                     env)))

(put 'eval 'begin (lambda (exp env)
     (eval-sequence (begin-actions exp) env)))

(put 'eval 'cond (lambda (exp env)
     (eval (cond->if exp) env)))

; changes on eval in a data-directed style
(define (eval exp env)
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((and (pair? exp) (not (eq? (get 'eval (car exp)) #f)))
         ((get 'eval (car exp)) exp env))
        ((pair? exp)
         (apply (eval (operator exp) env)
                (list-of-values (operands exp) env)))
        (else
          (error "Unknown expression type -- EVAL" exp))))

; sample program
(define prog '(define (append x y)
                (if (null? x)
                  y
                  (cons (car x)
                        (append (cdr x) y)))))

(user-print (eval prog the-global-environment)) (newline)
(user-print (eval '(append '(a b c) '(d e f)) the-global-environment)) (newline)
