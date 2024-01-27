(include "streams.scm")

(define (integral integrand initial-value dt)
  (define int
    (cons-stream initial-value
                 (add-streams (scale-stream integrand dt)
                              int)))
  int)

(define (RC R C dt)
  (lambda (i initial)
    (add-streams
      (scale-stream i R)
      (integral (scale-stream i (/ 1 C))
                initial dt))))

(define RC1 (RC 5 1 0.5))

(define ones (cons-stream 1 ones))
(define integers (cons-stream 1 (add-streams ones integers)))

(display-stream (RC1 integers 1))

