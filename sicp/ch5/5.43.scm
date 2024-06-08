(include "compiler-env.scm")

; the scan-out-defines procedure from 4.16
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

; changes on lambda-body
(define (lambda-body exp) (scan-out-defines (cddr exp)))

; changes on compile to support "let"
(define (compile exp target linkage env)
  (cond ((self-evaluating? exp)
         (compile-self-evaluating exp target linkage))
        ((quoted? exp) (compile-quoted exp target linkage))
        ((variable? exp)
         (compile-variable exp target linkage env))
        ((assignment? exp)
         (compile-assignment exp target linkage env))
        ((definition? exp)
         (compile-definition exp target linkage env))
        ((let? exp) (compile-if (let->combination exp) target linkage env))
        ((if? exp) (compile-if exp target linkage env))
        ((lambda? exp) (compile-lambda exp target linkage env))
        ((begin? exp)
         (compile-sequence (begin-actions exp)
                           target
                           linkage
                           env))
        ((cond? exp) (compile (cond->if exp) target linkage env))
        ((application? exp)
         (compile-application exp target linkage env))
        (else
         (error "Unknown expression type -- COMPILE" exp))))

; compile nested defines
(define prog '((define (f)
                 (define a 1)
                 (define b 2)
                 (* a b))))

(define code (compile prog 'val 'next '()))
(pretty-print code)
(newline)
