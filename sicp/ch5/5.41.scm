(include "syntax.scm")
(include "ec-evaluator-support.scm")

(define (address-frame address)
  (car address))

(define (address-offset address)
  (cdr address))

(define (lexical-address frame offset)
  (cons frame offset))

(define (find-variable var env)
  (define (find-var v e n)
    (cond ((null? e) #f)
          ((eq? v (address-frame e)) n)
          (else
            (find-var v (address-offset e) (+ n 1)))))
  (define (find-frame frames frame)
    (if (null? frames)
      'not-found
      (let ((found (find-var var (address-frame frames) 0)))
        (if found
          (lexical-address frame found)
          (find-frame (address-offset frames) (+ frame 1))))))
  (find-frame env 0))

(display (find-variable 'c '((y z) (a b c d e) (x y))))
(newline)

(display (find-variable 'x '((y z) (a b c d e) (x y))))
(newline)

(display (find-variable 'w '((y z) (a b c d e) (x y))))
(newline)
