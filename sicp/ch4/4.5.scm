(include "metacircular-evaluator.scm")

; check for => clause
(define (cond-arrow-clause? clause)
  (eq? (cadr clause) '=>))

(define (cond-arrow-test clause)
  (car clause))

(define (cond-arrow-recipient clause)
  (caddr clause))

; new version of "cond" evaluation to not used derived expressions
(define (eval-cond exp env)
  (define (eval-clauses clauses)
    (if (null? clauses)
      'false
      (let ((first (car clauses))
            (rest (cdr clauses)))
        (cond ((cond-else-clause? first)
               (if (null? rest)
                 (eval (sequence->exp (cond-actions first)) env)
                 (error "ELSE clause isn't last -- COND->IF" clauses)))
              ((cond-arrow-clause? first)
               (let ((value (eval (cond-arrow-test first) env)))
                 (if (true? value)
                   (apply
                     (eval (cond-arrow-recipient first) env)
                     (list value))
                   (eval-clauses rest))))
              (else
                (let ((pred (eval (cond-predicate first) env)))
                  (if (true? pred)
                    (eval (sequence->exp (cond-actions first)) env)
                    (eval-clauses rest))))))))
  (eval-clauses (cond-clauses exp)))

; changes on eval to evaluate conds
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
        ((cond? exp) (eval-cond exp env))
        ((application? exp)
         (apply (eval (operator exp) env)
                (list-of-values (operands exp) env)))
        (else
          (error "Unknown expression type -- EVAL" exp))))

; sample program
(define assoc-prog '(define (assoc key records)
                      (cond ((null? records) false)
                            ((equal? key (caar records)) (car records))
                            (else (assoc key (cdr records))))))

(define cond-prog '(cond ((assoc 'b '((a 1) (b 2))) => cadr)
                         (else false)))

(user-print (eval assoc-prog the-global-environment)) (newline)
(user-print (eval cond-prog the-global-environment)) (newline)
