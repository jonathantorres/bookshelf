(include "streams.scm")

; this is needed so that (random) works as expected
(set! *random-state* (random-state-from-platform))

(define (square x)
  (* x x))

(define (random-in-range low high)
  (let ((range (- high low)))
    (+ low (random range))))

(define (rand-range-stream low high)
  (cons-stream
    (random-in-range low high)
    (rand-range-stream low high)))

(define (monte-carlo s passed failed)
  (define (next passed failed)
    (cons-stream
      (/ passed (+ passed failed))
      (monte-carlo (stream-cdr s) passed failed)))
  (if (stream-car s)
    (next (+ passed 1) failed)
    (next passed (+ failed 1))))

(define (exp-stream x1 x2 y1 y2 r)
  (stream-map
    (lambda (x) (> r x))
    (add-streams
      (stream-map square (rand-range-stream x1 x2))
      (stream-map square (rand-range-stream y1 y2)))))

(define (pi-estimate)
  (scale-stream
    (monte-carlo (exp-stream -1.0 1.0 -1.0 1.0 1.0) 0 0)
    4.0))

(display-stream (pi-estimate))
