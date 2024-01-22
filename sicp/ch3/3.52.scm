(include "streams.scm")

(define sum 0)

(define (accum x)
  (set! sum (+ x sum))
  sum)

(define seq (stream-map accum (stream-enumerate-interval 1 20)))
(define y (stream-filter even? seq))
(define z (stream-filter (lambda (x) (= (remainder x 5) 0)) seq))

; Using guile, which evaluates with memoization
; The value of sum is: 10
(display sum) (newline)

; The value returned by stream-ref is: 136
(display (stream-ref y 7)) (newline)

; The stream with the multiples of 5 is: (10 15 45 55 105 120 190 210)
(display-stream z)
