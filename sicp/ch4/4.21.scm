(include "metacircular-evaluator.scm")

; a: computing fibonacci numbers
(define fib-prog '((lambda (n)
                    ((lambda (fib)
                       (fib fib n))
                     (lambda (f n)
                       (cond ((= n 0) 0)
                             ((= n 1) 1)
                             (else (+ (f f (- n 2)) (f f (- n 1)))))))) 10))

(user-print (eval fib-prog the-global-environment)) (newline)

; b: alternate definition of f
(define f-prog '(define (f x)
                  ((lambda (even? odd?)
                     (even? even? odd? x))
                   (lambda (ev? od? n)
                     (if (= n 0) true (od? ev? od? (- n 1))))
                   (lambda (ev? od? n)
                     (if (= n 0) false (ev? ev? od? (- n 1)))))))

(define f-run '(f 10))

(user-print (eval f-prog the-global-environment)) (newline)
(user-print (eval f-run the-global-environment)) (newline)
