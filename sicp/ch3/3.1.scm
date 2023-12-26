(define (make-accumulator sum)
  (lambda(amount)
    (set! sum (+ sum amount))
    sum))

(define A (make-accumulator 5))

(display (A 10)) (newline)
(display (A 10)) (newline)
