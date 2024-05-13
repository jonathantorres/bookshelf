(include "lazy-evaluator.scm")

(define (eval exp env)
  (cond ((self-evaluating? exp) exp)
        ((variable? exp) (lookup-variable-value exp env))
        ((quoted? exp) (eval-quotation exp))
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
         (apply (actual-value (operator exp) env)
                (operands exp)
                env))
        (else
         (error "Unknown expression type -- EVAL" exp))))

(define (eval-quotation exp)
  (let ((text (text-of-quotation exp)))
    (if (pair? text)
      (eval (list
              'cons
              (list 'quote (car text))
              (list 'quote (cdr text)))
            the-global-environment)
      text)))

; sample program
(define prog '(car '(a b c)))

(user-print (eval prog the-global-environment)) (newline)
