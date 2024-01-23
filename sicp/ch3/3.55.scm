(include "streams.scm")

(define ones (cons-stream 1 ones))
(define integers (cons-stream 1 (add-streams ones integers)))

(define (partial-sums s)
  (cons-stream (stream-car s)
               (add-streams (partial-sums s) (stream-cdr s))))

(define sums (partial-sums integers))

(display-stream sums)

