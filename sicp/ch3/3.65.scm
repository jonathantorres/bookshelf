(include "streams.scm")

(define (partial-sums s)
  (cons-stream (stream-car s)
               (add-streams (partial-sums s) (stream-cdr s))))

(define (log2 n)
  (cons-stream (/ 1.0 n)
               (stream-map (lambda (x) (- x)) (log2 (+ n 1)))))

(define log-stream (partial-sums (log2 1)))

(display-stream log-stream)
